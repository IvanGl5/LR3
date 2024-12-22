#ifndef PIPE_H
#define PIPE_H

#include <iostream>
#include <string>
#include <unordered_map>

class DataManager;

class Pipe {
private:
    int id;
    std::string name;
    double length = 0;
    double diameter = 0;
    bool repairStatus = false;

public:
    static int nextId;
    static std::unordered_map<int, Pipe> pipes;

    Pipe() = default;
    Pipe(int id, const std::string& name, double length, double diameter, bool repairStatus);

    friend std::ostream& operator<<(std::ostream& out, const Pipe& pipe);

    static void printPipeInfo(std::ostream& out);
    friend class DataManager;

    void readFromConsole();
    void writeToConsole() const;
    void editRepairStatus();

    int getId() const { return id; }
    void setId(int newId) { id = newId; }

    static void addPipe();
    static void displayAll();

    static std::vector<Pipe> findPipes();

    static void displayPipes(const std::vector<Pipe>& pipes);

    static void deletePipeMenu();
    static void editPipeById();
    static int pipeSubMenu();
    static void selectPipesForBatchEditOrDelete();
    static void batchEditOrDeleteMenu(const std::vector<Pipe>& pipesToEdit);
};

#endif