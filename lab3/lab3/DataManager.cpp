#include <iostream>
#include <fstream>
#include <unordered_map>
#include "Pipe.h"
#include "CS.h"
#include "DataManager.h"
#include <filesystem>

std::string DataManager::getFullPathFromCurrentDirectory() {
    try {
        std::string currentPath = std::filesystem::current_path().string();

        std::string filename;
        std::cout << "������� �������� �����: ";
        std::getline(std::cin, filename);

        std::string fullPath = currentPath + "/" + filename;

        return fullPath;
    }
    catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "������ ��� ��������� ������� ����������: " << e.what() << std::endl;
        return "";
    }
}

void DataManager::saveToFile(const std::unordered_map<int, Pipe>& pipes, const std::unordered_map<int, CompressorStation>& stations, const std::string& filename) {
    std::ofstream outFile(filename);
    if (outFile.is_open()) {
        for (const auto& [id, pipe] : pipes) {
            if (!pipe.name.empty()) {
                outFile << "PIPE" << std::endl;
                outFile << pipe.id << std::endl;
                outFile << pipe.name << std::endl;
                outFile << pipe.length << std::endl;
                outFile << pipe.diameter << std::endl;
                outFile << (pipe.repairStatus ? "1" : "0") << std::endl;
            }
        }

        for (const auto& [id, station] : stations) {
            if (!station.name.empty()) {
                outFile << "CS" << std::endl;
                outFile << station.id << std::endl;
                outFile << station.name << std::endl;
                outFile << station.workshopNumber << std::endl;
                outFile << station.workshopNumberInWork << std::endl;
                outFile << station.efficiency << std::endl;
            }
        }

        outFile.close();
        std::cout << "������ ��������� � ���� " << filename << std::endl;
    }
    else {
        std::cerr << "�� ������� ������� ���� ��� ������: " << filename << std::endl;
    }
}

void DataManager::loadFromFile(std::unordered_map<int, Pipe>& pipes, std::unordered_map<int, CompressorStation>& stations, const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile.is_open()) {
        std::cerr << "������ ��� �������� ����� ��� ������: " << filename << "\n";
        return;
    }

    pipes.clear();
    stations.clear();

    std::string line;
    while (std::getline(inFile, line)) {
        if (line == "PIPE") {
            Pipe pipe;
            int id;

            inFile >> id;
            inFile.ignore();

            std::getline(inFile, pipe.name);
            inFile >> pipe.length;
            inFile >> pipe.diameter;
            inFile >> pipe.repairStatus;
            inFile.ignore();

            pipe.id = id;
            pipes[id] = pipe;
        }
        else if (line == "CS") {
            CompressorStation station;
            int id;

            inFile >> id;
            inFile.ignore();

            std::getline(inFile, station.name);
            inFile >> station.workshopNumber;
            inFile >> station.workshopNumberInWork;
            inFile >> station.efficiency;
            inFile.ignore();

            station.id = id;
            stations[id] = station;
        }
    }

    inFile.close();
    std::cout << "������ ������� ��������� �� �����: " << filename << "\n";
}