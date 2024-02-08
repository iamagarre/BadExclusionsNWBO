#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>



namespace fs = std::filesystem;

const int FILENAME_TRUNCATION_LENGTH = 17;
const int RESULT_THRESHOLD = 7;

void CopyFileToAllFolders(const std::string& filePath, const std::string& destinationPath) {
    try {
        if (!fs::is_directory(destinationPath)) {
            std::cout << "Destination path is not a valid directory.\n";
            return;
        }

        for (const auto& dirEntry : fs::recursive_directory_iterator(destinationPath)) {
            try {
                if (fs::is_directory(dirEntry)) {
                    std::filesystem::path folderPath = dirEntry.path() / fs::path(filePath).filename();

                    fs::copy_file(filePath, folderPath, fs::copy_options::overwrite_existing);

                    std::string command = "\"" + folderPath.string() + "\" > result.txt";
                    int systemResult = std::system(command.c_str());

                    if (systemResult == 0) {
                        std::ifstream resultFile("result.txt");
                        if (resultFile.is_open()) {
                            std::string resultString;
                            std::getline(resultFile, resultString);
                            resultFile.close();

                            int result = std::stoi(resultString);

                            if (result <= RESULT_THRESHOLD) {
                                std::cout << "Excluded folder found: " << folderPath.string().substr(0, folderPath.string().length() - FILENAME_TRUNCATION_LENGTH) << "\n";
                            }
                        }
                    }
                    else {
                        std::cerr << "Error executing command for: " << folderPath.string() << "\n";
                    }
                }
            }
            catch (const std::exception& e) {
                std::cerr << "Error processing directory: " << dirEntry.path().string() << "\n";
                std::cerr << "Error message: " << e.what() << "\n";
            }
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error accessing the destination path.\n";
        std::cerr << "Error message: " << e.what() << "\n";
    }
}

//Create folders from list file
void processListFile(const char* listFilePath) {
    FILE* listFile = fopen(listFilePath, "r");
    if (listFile == NULL) {
        //fprintf(stderr, "Unable to open list file %s: %s\n", listFilePath, strerror(errno));
        exit(1);
    }

    char folderName[MAX_PATH_LENGTH];
    while (fgets(folderName, sizeof(folderName), listFile) != NULL) {
        //Remove newline characters
        size_t len = strlen(folderName);
        if (len > 0 && (folderName[len - 1] == '\n' || folderName[len - 1] == '\r')) {
            folderName[len - 1] = '\0';
        }

        if (_mkdir(folderName) != 0) {
            //fprintf(stderr, "Unable to create folder %s: %s\n", folderName, strerror(errno));
        }
    }

    fclose(listFile);
}

// Help message
void helpMessage() {
    fprintf(stderr, "Usage: BadExclusionsNWBO.exe -p <Path> [-l <ListFilePath>]\n\n");
    fprintf(stderr, "Arguments:\n");
    fprintf(stderr, " -p <Path>:      folder to check for exclusions. It will check all subfolders where you have write permissions.\n");
    fprintf(stderr, " -l <ListFile>:  specify a txt file that contains a list of folders to create.\n");
    fprintf(stderr, "\nBadExclusionsNWBO v1.0\n\n");
}

int main(int argc, char* argv[]) {
    // Print header and version information
    printf("\n__________             .______________             .__               .__                      \n");
    printf("\\______   \\_____     __| _/\\_   _____/__  ___ ____ |  |  __ __  _____|__| ____   ____   ______\n");
    printf(" |    |  _/\\__  \\   / __ |  |    __)_\\  \\/  // ___\\|  | |  |  \\/  ___/  |/  _ \\ /    \\ /  ___/\n");
    printf(" |    |   \\ / __ \\_/ /_/ |  |        \\>    <\\  \\___|  |_|  |  /\\___ \\|  (  <_> )   |  \\\\___ \\ \n");
    printf(" |______  /(____  /\\____ | /_______  /__/\\_ \\\\___  >____/____//____  >__|\\____/|___|  /____  >\n");
    printf("        \\/      \\/      \\/         \\/      \\/    \\/                \\/               \\/     \\/ \n");
    printf("\nNow With Better Opsec!\n\n");

    if (argc < 3) {
        helpMessage();
        return 1;
    }

    std::string filePath = "Hook_Checker.exe";
    std::string destinationPath;

    // Check for the optional -l parameter
    if (std::string(argv[1]) == "-l" && argc >= 4) {
        std::string listFilePath = argv[2];
        destinationPath = argv[4];

        std::cout << "[+] Creating directories from the list file: " << listFilePath << " inside " << destinationPath << "...\n\n";
        CreateDirectoriesFromFile(listFilePath, destinationPath);
    }
    else if (std::string(argv[1]) == "-p" && argc >= 3) {
        destinationPath = argv[2];

        std::cout << "[+] Running " << filePath << " on all folders/subfolders inside " << destinationPath << "...\n\n";
        CopyFileToAllFolders(filePath, destinationPath);
    }
    else {
        helpMessage();
        return 1;
    }

    std::cout << "\n[+] Done!\n";

    return 0;
}
