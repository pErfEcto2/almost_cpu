#include "../headers/mainwindow.h"
#include "../headers/command.h"
#include "../headers/lib.h"
#include "../headers/memory.h"
#include "ui_mainwindow.h"
#include "../headers/vector.h"
#include "../headers/cpu.h"
#include <QIntValidator>
#include <QFileDialog>
#include <fstream>

#define MEM_SIZE 1024


/*
 * TODO:
 * fix bug when using variable(before .code section) which starts with "M"
 * realtime updates
 * memory transform in the CPU(i guess...)
 * add virtual monitor & functions to draw
*/

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    ui->breakpoint_line->setValidator(new QIntValidator(0, 99999));
    ui->number_of_cores_line->setValidator(new QIntValidator(0, 99));

    mem = new Memory(MEM_SIZE);
    cpu = NULL;
}

MainWindow::~MainWindow() {
    delete ui;
    delete mem;
    delete cpu;
}

void MainWindow::on_save_button_clicked() {
    QString file_path = QFileDialog::getSaveFileName(this, "Select file");
    if (!file_path.endsWith(".ass")) {
        file_path += ".ass";
    }

    std::ofstream file(file_path.toStdString());
    file << (ui->code_editor->toPlainText().toStdString());
    file.close();
}

void MainWindow::on_import_button_clicked() {
    QString file_path = QFileDialog::getOpenFileName(this, "Select file", "", "ASSembly lang (*.ass)");
    std::ifstream file(file_path.toStdString());
    std::string s;

    ui->code_editor->clear();
    while (std::getline(file, s))
        ui->code_editor->append(QString::fromStdString(s));

    file.close();
}

void MainWindow::perror(std::string s) {
    ui->text_to_show->setPlainText(QString::fromStdString(s));
}

void MainWindow::on_run_button_clicked() {
    QString num_of_cores = ui->number_of_cores_line->text();
    if (num_of_cores.size() == 0) num_of_cores = "2";
    else if (num_of_cores == "0") {
        perror("invalid number of cores");
        return;
    }

    QString bp_s = ui->breakpoint_line->text();
    int breakpoint = -1;
    if (bp_s.size() != 0) breakpoint = bp_s.toInt();

    Vector<std::string> src = str_split(ui->code_editor->toPlainText().toStdString(), '\n');
    for (auto &s : src) {
        s = trim(s);
    }

    bool isData = true;
    std::map<std::string, unsigned int> labels;
    std::map<std::string, unsigned int> variables;
    Vector<Command> commands;
    int i = 0;

    // FINDING LABELS
    for (std::string &line : src.find(".code")) {
        if (line == ".code" || line.size() < 2)
            continue;
        else if (line.back() != ':') {
            i++;
            continue;
        }
        if (labels.find(line) != labels.end()) {
            perror("redefintion of the label " + line);
            return;
        }
        labels[line] = i;
    }

    i = 0;
    // COMPILATION
    for (std::string &line : src) {
        if (line == ".data" || line.size() == 0 || line[0] == ';')
            continue;
        if (line == ".code") {
            isData = false;
            i = 0;
            continue;
        }

        if (isData) {
            std::string var_name;
            std::string str_value;
            try {
                var_name = trim(str_split(line, '=')[0]);
                str_value = trim(str_split(line, '=')[1]);
            } catch (std::exception &e) {
                perror("invalid syntax in  .data section");
                return;
            }
            if (var_name.size() == 0 || str_value.size() == 0) {
                perror("invalid name or value in .data section");
                return;
            }
            if (variables.find(var_name) != variables.end()) {
                perror("redefinition of " + var_name);
                return;
            }
            if (is_reg_or_mem(var_name)) {
                perror("invalid variable name: " + var_name);
                return;
            }


            unsigned int val;
            try {
                    val = str2uint(str_value);
            } catch (std::invalid_argument &e) {
                perror("invalid value: " + str_value);
                return;
            }

            if (i >= mem->size) {
                perror("not enough memory");
                return;
            }

            variables[var_name] = i;
            (*mem)[i].value = val;
            i++;
        } else if (breakpoint != 0){
            Vector<std::string> command_and_opers;
            for (auto &el : str_split(line, ' ')) {
                if (el.size() > 0)
                    command_and_opers.push_back(trim(el));
            }
            Command command;

            std::string instr = command_and_opers[0];
            if (instr.back() == ':')
                continue; // if line is a label
            else if (instr == "mov")
                command.type = Type::mov;
            else if (instr == "sum")
                command.type = Type::sum;
            else if (instr == "sumu")
                command.type = Type::sumu;
            else if (instr == "sumf")
                command.type = Type::sumf;
            else if (instr == "inc")
                command.type = Type::inc;
            else if (instr == "incu")
                command.type = Type::incu;
            else if (instr == "incf")
                command.type = Type::incf;
            else if (instr == "mul")
                command.type = Type::mul;
            else if (instr == "mulf")
                command.type = Type::mulf;
            else if (instr == "mulu")
                command.type = Type::mulu;
            else if (instr == "jmp")
                command.type = Type::jmp;
            else if (instr == "strthread")
                command.type = Type::strthread;
            else if (instr == "hlt")
                command.type = Type::hlt;
            else if (instr == "push")
                command.type = Type::push;
            else if (instr == "pop")
                command.type = Type::pop;
            else if (instr == "cmp")
                command.type = Type::cmp;
            else if (instr == "je")
                command.type = Type::je;
            else if (instr == "jne")
                command.type = Type::jne;
            else if (instr == "slp")
                command.type = Type::slp;
            else {
                perror("unknown instruction '" + instr + "' in line: \n" + line);
                return;
            }

            breakpoint--;

            try {
                if (is_num(command_and_opers[1])) {
                    perror("cannot use rvalue '" + command_and_opers[1] + "' in line:\n" + line);
                    return;
                }

                switch (command.type) {
                // two operands
                case Type::mov:
                case Type::sum:
                case Type::sumu:
                case Type::sumf:
                case Type::mul:
                case Type::mulf:
                case Type::mulu:
                case Type::cmp:
                    if (variables.find(command_and_opers[1]) != variables.end())
                        command.operA = "m" + std::to_string(variables[command_and_opers[1]]);
                    else if (is_reg_or_mem(command_and_opers[1]))
                        command.operA = transform_memory(command_and_opers[1], variables);
                    else {
                        perror("undefined variable '" + command_and_opers[1] + "' in line:\n" + line);
                        return;
                    }

                    if (variables.find(command_and_opers[2]) != variables.end())
                        command.operB = "m" + std::to_string(variables[command_and_opers[2]]);
                    else if (is_num(command_and_opers[2]) || is_reg_or_mem(command_and_opers[2]))
                        command.operB = transform_memory(command_and_opers[2], variables);
                    else {
                        perror("undefined variable '" + command_and_opers[2] + "' in line:\n" + line);
                        return;
                    }

                    if (command.operA == command.operB && command.type == Type::mov) {
                        perror("cant use same args in the mov instruction in line:\n" + line);
                        return;
                    }

                    break;

                // one operand
                case Type::inc:
                case Type::incf:
                case Type::incu:
                case Type::push:
                case Type::pop:
                case Type::slp:
                    if (variables.find(command_and_opers[1]) != variables.end())
                        command.operA = std::to_string(variables[command_and_opers[1]]);
                    else if (is_reg_or_mem(command_and_opers[1]))
                        command.operA = transform_memory(command_and_opers[1], variables);
                    else {
                        perror("undefined variable '" + command_and_opers[1] + "' in line:\n" + line);
                        return;
                    }

                    break;

                // label as operand
                case Type::jmp:
                case Type::je:
                case Type::jne:
                case Type::strthread:
                    if (labels.find(command_and_opers[1] + ":") != labels.end())
                        command.operA = std::to_string(labels[command_and_opers[1] + ":"]);
                    else {
                        perror("undefined label '" + command_and_opers[1] + "' in line:\n" + line);
                        return;
                    }

                    break;

                // no operands(hlt)
                case Type::hlt:
                    break;
                }
            } catch (std::exception &e) {
                perror("invalid syntax in line:\n" + line);
                return;
            }

            commands.push_back(command);
        }
    }

    cpu = new CPU(commands, *mem, num_of_cores.toInt());

    try {
        cpu->run();
    } catch (std::exception &e) {
        perror("runtime error:\n" + std::string(e.what()));
        return;
    }

    print_info();
    delete cpu;
}

void MainWindow::print_info() {
    std::string status{"First " + std::to_string((int)(mem->size * 0.1)) + " elems of the memory:\n"};
    for (int i{0}; i < (int)(mem->size * 0.1); i++) status += uint2hex((*mem)[i].value) + " ";
    status += "\n\n\n" + cpu->getStatus();
    ui->text_to_show->setPlainText(QString::fromStdString(status));
}

void MainWindow::on_get_desc_button_clicked() {
    std::string res{"Docs:\n"
"1) all lines with semicolon(;) at the beginning are considered as comments\n\n"
"2) every line before '.code' section is consider '.data' section\n\n"
"3) in the '.data' section every line must match the given syntax: variable_name = int_or_float_value\n\n"
"4) redefinitions of variables or labels are forbidden\n\n"
"5) every line after '.code' line is consider in the '.code' section no matter if there're '.data' or '.code' lines\n\n"
"6) every line in the '.code' section must match the given syntax: instruction oper1_or_empty oper2_or_empty\n\n"
"7) 'A', 'B', 'r1' and 'r2' are names of registers. First two are common for all cores. Each core has last two registers\n\n"
"8) arguments in instructions are either a variable name, a memory address(a number, which starts with 'm' letter) or a number\n\n"
"9) you can specify number of cores in the 'number of cores' line. Default is 2\n"
"10) you can specify a breakpoint(aka last instruction to be executed) in the 'breakpoint' line\n\n"
"11) you can run code by pressing Ctrl+r and get docs by pressing Ctrl+d\n\n\n"
"Here is a list of instructions:\n"};
    for (int t = Type::mov; t != Type::hlt + 1; t++) {
        res += "\n" + std::to_string(t + 1) + ") " + Command(static_cast<Type>(t)).desc() + "\n";
    }
    ui->text_to_show->setPlainText(QString::fromStdString(res));
}
