#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <sstream>

//SETUP GRID (SIZE)
void getGridDimensions(int &grid_width_ref, int &grid_height_ref)
{
    std::string first_line {};
    std::getline(std::cin, first_line);
    
    //remove words
    for(char &c : first_line)
    {
        if(!std::isdigit(c))
            c = ' ';
    }
    
    std::stringstream ss(first_line);
    
    try
    {
        ss >> grid_width_ref >> grid_height_ref;
    }
    catch (...)
    {
        std::cout << "Error: No two valid numbers found.";
    }
}

//GRID WORDS
void readGridWords(const int &grid_width_ref, const int &grid_height_ref, std::vector<std::string> &grid_words_ref)
{
    for(int i{0}; i < grid_height_ref; i++)
    {
        std::string word {};
        std::cin >> word;
        while(static_cast<int>(word.size()) < grid_width_ref)
        {
            std::cin >> word;
        }
        grid_words_ref.push_back(word);
    }
}

void printGridWords(const std::vector<std::string> &grid_words_ref)
{
    std::cout << "Original Grid:\n";
    for(int i {0}; i < static_cast<int>(grid_words_ref.size()); i++)
    {
        std::cout << grid_words_ref.at(i) << '\n';
    }
    std::cout << '\n';
}

//SEARCH WORDS
void readSearchWords(std::vector<std::string> &search_words_ref)
{
    std::string word {};
    while(std::getline(std::cin, word))
    {
        if(!word.empty())
        {
            search_words_ref.push_back(word);
        }
    }
    search_words_ref.erase(search_words_ref.begin()); //removes "words:" input from vector
}

void printSearchWords(const std::vector<std::string> &search_words_ref)
{
    std::cout << "Words to look for:\n";
    for(int i {0}; i < static_cast<int>(search_words_ref.size()); i++)
    {
        std::cout << search_words_ref.at(i) << '\n';
    }
}

void solveWordSearch(std::vector<std::string> &grid_words, const std::vector<std::string> &search_words) {
    //Directions
    std::vector<int> row_dir = {-1, -1, 0, 1, 1, 1, 0, -1};
    std::vector<int> col_dir = {0, 1, 1, 1, 0, -1, -1, -1};
    
    //initialize row size and column size & copy grid words
    int rows = static_cast<int>(grid_words.size());
    int cols = static_cast<int>(grid_words.at(0).size());
    std::vector<std::string> capitalizedGrid = grid_words;
    
    //print original grid
    std::cout << "Original Grid:\n";
    for (const std::string& row : grid_words) std::cout << row << "\n";
    
    //print words discovered and location
    std::cout << "\nWords Discovered:\n";

    for (const std::string& word : search_words)
    {
        bool found = false;
        //iterate through rows, columns, and check diagonals and adjacents to find word branch
        for (int r {0}; r < rows; ++r)
        {
            for (int c {0}; c < cols; ++c)
            {
                for (int dir {0}; dir < 8; ++dir)
                {
                    int k {};
                    for (k = 0; k < static_cast<int>(word.size()); ++k)
                    {
                        int nr = r + k * row_dir.at(dir);
                        int nc = c + k * col_dir.at(dir);
                        if (nr < 0 || nr >= rows || nc < 0 || nc >= cols || std::tolower(grid_words.at(nr).at(nc)) != std::tolower(word.at(k)))
                        {
                            break;
                        }
                    }
                    
                    if (k == static_cast<int>(word.size()))
                    {
                        int row_end = r + (static_cast<int>(word.size()) - 1) * row_dir.at(dir);
                        int col_end = c + (static_cast<int>(word.size()) - 1) * col_dir.at(dir);
                        
                        std::cout << word << " found at (" << c << ", " << r << ") to ("
                             << col_end << ", " << row_end << ")\n";
                        // Capitalize found word in the output grid
                        for (int i {0}; i < static_cast<int>(word.size()); ++i)
                        {
                            capitalizedGrid.at(r + i * row_dir.at(dir)).at(c + i * col_dir.at(dir)) =
                                std::toupper(capitalizedGrid.at(r + i * row_dir.at(dir)).at(c + i * col_dir.at(dir)));
                        }
                        found = true;
                        break;
                    }
                }
                if (found) break;
            }
            if (found) break;
        }
    }

    std::cout << "\nFound Words Capitalized:\n";
    for (const std::string& row : capitalizedGrid)
    {
        std::cout << row << "\n";
    }
}

int main()
{
    //Read first line for dimensions
    int grid_width {0};
    int &grid_width_ref {grid_width};
    
    int grid_height {0};
    int &grid_height_ref {grid_height};
    
    getGridDimensions(grid_width_ref, grid_height_ref);
    
    //Read grid to vector
    std::vector<std::string> grid_words{};
    std::vector<std::string> &grid_words_ref {grid_words};
    
    readGridWords(grid_width_ref, grid_height_ref, grid_words_ref);
    
    //print grid
//    printGridWords(grid_words_ref);
    
    //Read search keys to vector
    std::vector<std::string> search_words{};
    std::vector<std::string> &search_words_ref {search_words};
    
    readSearchWords(search_words_ref);
    
    //print search keys
//    printSearchWords(search_words_ref);
    
    
    solveWordSearch(grid_words_ref, search_words_ref);
    
    
  return 0;
}
