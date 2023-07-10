#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>

namespace fs = std::filesystem;

void CopyFileToAllFolders(const std::string& filePath, const std::string& destinationPath)
{
    try
    {
        // Check if the destination path exists and is a directory
        if (!fs::is_directory(destinationPath))
        {
            std::cout << "Destination path is not a valid directory.\n";
            return;
        }

        // Iterate over all directories in the destination path
        for (const auto& dirEntry : fs::recursive_directory_iterator(destinationPath))
        {
            try
            {
                if (fs::is_directory(dirEntry))
                {
                    // Concatenate the file name to the current directory path
                    std::string newFilePath = dirEntry.path().string() + "\\" + fs::path(filePath).filename().string();

                    // Copy the file to the current directory
                    fs::copy_file(filePath, newFilePath, fs::copy_options::overwrite_existing);

                    // Execute the copied file and get the result
                    std::string command = "\"" + newFilePath + "\" > result.txt";
                    system(command.c_str());

                    // Read the result from the file
                    std::ifstream resultFile("result.txt");
                    if (resultFile.is_open())
                    {
                        std::string resultString;
                        std::getline(resultFile, resultString);
                        resultFile.close();

                        // Convert the result to a number
                        int result = std::stoi(resultString);

                        // Define the threshold value
                        int threshold = 7; // Modify this variable to change the threshold

                        // Check if the result is below the threshold and print the path
                        if (result <= threshold)
                        {
                            std::cout << "Excluded folder found: " << newFilePath.substr(0, newFilePath.length() - 17) << "\n";
                        }
                    }
                }
            }
            catch (const std::exception& e)
            {
                //std::cout << "Error while processing directory: " << dirEntry.path().string() << "\n";
                //std::cout << "Error message: " << e.what() << "\n";
            }
        }
    }
    catch (const std::exception& e)
    {
        //std::cout << "Error accessing the destination path.\n";
        //std::cout << "Error message: " << e.what() << "\n";
    }
}

int main(int argc, char* argv[])
{
    //ASCII art
    printf("__________             .______________             .__               .__                      \n");
    printf("\\______   \\_____     __| _/\\_   _____/__  ___ ____ |  |  __ __  _____|__| ____   ____   ______\n");
    printf(" |    |  _/\\__  \\   / __ |  |    __)_\\  \\/  // ___\\|  | |  |  \\/  ___/  |/  _ \\ /    \\ /  ___/\n");
    printf(" |    |   \\ / __ \\_/ /_/ |  |        \\>    <\\  \\___|  |_|  |  /\\___ \\|  (  <_> )   |  \\\\___ \\ \n");
    printf(" |______  /(____  /\\____ | /_______  /__/\\_ \\\\___  >____/____//____  >__|\\____/|___|  /____  >\n");
    printf("        \\/      \\/      \\/         \\/      \\/    \\/                \\/               \\/     \\/ \n");
    printf("\nNow With Better Opsec...\n\n");

    if (argc < 3)
    {
        std::cout << "Usage: BadExclusionsNWBO.exe -p [folder_path]\n";
        return 1;
    }

    std::string filePath = "Hook_Checker.exe";
    std::string destinationPath = argv[2];

    std::cout << "[+] Running " << filePath << " on all folders/subfolders inside " << destinationPath << "...\n\n";
    CopyFileToAllFolders(filePath, destinationPath);

    std::cout << "\n[+] Done!\n";

    return 0;
}
