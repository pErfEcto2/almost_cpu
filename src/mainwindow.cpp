#include "../headers/mainwindow.h"
#include "../headers/command.h"
#include "../headers/lib.h"
#include "../headers/memory.h"
#include "ui_mainwindow.h"
#include "../headers/vector.h"
#include <iostream>
#include <map>
#include "../headers/cpu.h"
#include <QIntValidator>


#define MEM_SIZE 1024

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    ui->breakpoint_line->setValidator(new QIntValidator(0, 99999));
    ui->number_of_cores_line->setValidator(new QIntValidator(0, 65));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_run_button_clicked() {
    QString num_of_cores = ui->number_of_cores_line->text();
    if (num_of_cores.size() == 0) num_of_cores = "4";

    QString bp_s = ui->breakpoint_line->text();
    int breakpoint = -1;
    if (bp_s.size() != 0) breakpoint = bp_s.toInt();

    Vector<std::string> src =
        str_split(ui->code_editor->toPlainText().toStdString(), '\n');
    for (auto &s : src) {
        s = trim(s);
    }

    bool isData = true;
    std::map<std::string, unsigned int> labels;
    std::map<std::string, unsigned int> variables;
    Memory mem(MEM_SIZE);
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
            ui->text_to_show->setPlainText(
                QString::fromStdString("redefintion of the label " + line));
            return;
        }
        labels[line] = i;
    }

    i = 0;
    // COMPILE PROCESS
    for (std::string &line : src) {
        if (line == ".data" || line.size() == 0)
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
                ui->text_to_show->setPlainText(
                    QString::fromStdString("invalid syntax in  .data section"));
                return;
            }
            if (var_name.size() == 0 || str_value.size() == 0) {
                ui->text_to_show->setPlainText(
                    QString::fromStdString("invalid name or value in .data section"));
                return;
            }
            if (variables.find(var_name) != variables.end()) {
                ui->text_to_show->setPlainText(
                    QString::fromStdString("redefinition of " + var_name));
                return;
            }
            if (var_name == "A" || var_name == "B" || var_name == "r1" || var_name == "r2") {
                ui->text_to_show->setPlainText(
                    QString::fromStdString("invalid variable name: " + var_name));
                return;
            }


            unsigned int val;
            try {
                    val = str2uint(str_value);
            } catch (std::invalid_argument &e) {
                ui->text_to_show->setPlainText(
                    QString::fromStdString("invalid value: " + str_value));
                return;
            }

            if (i >= mem.size) {
                    ui->text_to_show->setPlainText(
                    QString::fromStdString("not enough memory"));
                    return;
            }

            variables[var_name] = i;
            mem[i].value = val;
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
            else {
                ui->text_to_show->setPlainText(QString::fromStdString(
                    "unknown instruction '" + instr + "' in line: \n" + line));
                return;
            }

            breakpoint--;

            try {
                if (is_num(command_and_opers[1])) {
                    ui->text_to_show->setPlainText(QString::fromStdString("cannot use lvalue '" + command_and_opers[1] + "' in line:\n" + line));
                    return;
                }
                switch (command.type) {
                case Type::mov:
                case Type::sum:
                case Type::sumu:
                case Type::sumf:
                case Type::mul:
                case Type::mulf:
                case Type::mulu:
                    if (variables.find(command_and_opers[1]) != variables.end())
                        command.operA = "m" + std::to_string(variables[command_and_opers[1]]);
                    else if (is_num(command_and_opers[1]) || command_and_opers[1] == "A" || command_and_opers[1] == "B" ||
                               command_and_opers[1] == "r1" || command_and_opers[1] == "r2" || command_and_opers[1][0] == 'm')
                        command.operA = command_and_opers[1];
                    else {
                            ui->text_to_show->setPlainText(
                                QString::fromStdString("undefined variable '" + command_and_opers[1] + "' in line:\n" + line));
                            return;
                    }

                    if (variables.find(command_and_opers[2]) != variables.end())
                            command.operB = "m" + std::to_string(variables[command_and_opers[2]]);
                    else if (is_num(command_and_opers[2]) || command_and_opers[2] == "A" || command_and_opers[2] == "B" ||
                               command_and_opers[2] == "r1" || command_and_opers[2] == "r2" || command_and_opers[2][0] == 'm')
                        command.operB = command_and_opers[2];
                    else {
                            ui->text_to_show->setPlainText(
                                QString::fromStdString("undefined variable '" + command_and_opers[2] + "' in line:\n" + line));
                            return;
                    }

                    break;

                case Type::inc:
                case Type::incf:
                case Type::incu:
                    if (variables.find(command_and_opers[1]) != variables.end())
                            command.operA = std::to_string(variables[command_and_opers[1]]);
                    else if (is_num(command_and_opers[1]) || command_and_opers[1] == "A" || command_and_opers[1] == "B" ||
                             command_and_opers[1] == "r1" || command_and_opers[1] == "r2" || command_and_opers[1][0] == 'm')
                        command.operA = command_and_opers[1];
                    else {
                            ui->text_to_show->setPlainText(
                                QString::fromStdString("undefined variable '" + command_and_opers[1] + "' in line:\n" + line));
                            return;
                    }

                    break;

                case Type::jmp:
                case Type::strthread:
                    if (labels.find(command_and_opers[1] + ":") != labels.end())
                            command.operA = std::to_string(labels[command_and_opers[1] + ":"]);
                    else {
                            ui->text_to_show->setPlainText(
                                QString::fromStdString("undefined label '" + command_and_opers[1] + "' in line:\n" + line));
                            return;
                    }

                    break;
                }
            } catch (std::exception &e) {
                ui->text_to_show->setPlainText(
                    QString::fromStdString("invalid syntax in line:\n" + line));
                return;
            }

            commands.push_back(command);
        }
    }

    // commands.push_back(Command(Type::hlt));

    CPU cpu(commands, mem, num_of_cores.toInt());
    try {
        cpu.run();
    } catch (std::exception &e) {
        ui->text_to_show->setPlainText(
            QString::fromStdString("runtime error:\n" + std::string(e.what())));
        return;
    }

    std::string status{"First " + std::to_string((int)(mem.size * 0.1)) + " elems of the memory:\n"};

    for (int i{0}; i < (int)(mem.size * 0.1); i++) status += uint2hex(mem[i].value) + " ";

    status += "\n\n" + cpu.getStatus();

    ui->text_to_show->setPlainText(QString::fromStdString(status));
}

void MainWindow::on_get_desc_button_clicked() {
    std::string res{"Docs:\n"
"1) all empty lines are ignored\n\n"
"2) every line before '.code' section is consider '.data' section\n\n"
"3) in the '.data' section every line must match the given regex: '\s*.+\s*=\s*\d(\.\d+)?\s*'\n\n"
"4) redefinitions of variables or labels are forbidden\n\n"
"5) every line after '.code' line is consider in the '.code' section no matter if there're '.data' or '.code' lines\n\n"
"6) every line in the '.code' section must match the given regex: '\s*.+(\s+.+)?(\s+.+)?\s*'\n(<instruction> <oper1 or empty> <oper2 or empty>)\n\n"
"7) 'A', 'B', 'r1' and 'r2' are names of registers. First two are common for all cores. Each core has last two registers\n\n"
"8) arguments in instructions are either a variable name, a memory address(a number, which starts with 'm' letter) or a number\n\n"
"9) you can specify number of cores in the 'number of cores' line. Default is 4\n\n"
"10) you can specify a breakpoint(aka last instruction to be executed) in the 'breakpoint' line\n\n"
"11) you can run code by pressing Ctrl+r and get docs by pressing Ctrl+d\n\n\n"
"Here is a list of instructions:\n"};
    for (int t = Type::mov; t != Type::hlt + 1; t++) {
        res += "\n" + std::to_string(t + 1) + ") " + Command(static_cast<Type>(t)).desc() + "\n";
    }
    ui->text_to_show->setPlainText(QString::fromStdString(res));
}

