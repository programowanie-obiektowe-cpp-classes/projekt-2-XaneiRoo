#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm> 
#include <ranges>

auto Taniec(const std::string& uklad)
{
    return uklad | std::views::split(',') |
           std::views::transform([](auto&& rng) { 
        return std::string(rng.begin(), rng.end()); }) |
           std::ranges::to< std::vector< std::string > >();


}

std::string dzien16a(const std::vector< std::string >& ruchy, std::string programy)
{
    

    for (auto i = 0; i != ruchy.size(); i++)
    {
        std::string aktualny_ruch = ruchy[i];
        char        typ           = aktualny_ruch.front();
        
        std::string parametry = aktualny_ruch.substr(1);

        if (typ == 's')
        {
            int spin = std::stoi(parametry);
            std::rotate(programy.begin(), programy.end() - spin, programy.end());
        }
        else if (typ == 'x')
        {
            size_t zmiana_poz = parametry.find('/');
            int    pozA       = std::stoi(parametry.substr(0, zmiana_poz));
            int    pozB       = std::stoi(parametry.substr(zmiana_poz + 1));

            std::swap(programy[pozA], programy[pozB]);

        }
        else if (typ == 'p')
        {
            char charA = parametry[0];
            char charB = parametry[2]; 


            auto itA = std::find(programy.begin(), programy.end(), charA);
            auto itB = std::find(programy.begin(), programy.end(), charB);


            std::iter_swap(itA, itB);
        }
        
    }
    return programy;
}

std::string dzien16b(const std::vector< std::string >& ruchy, std::string programy)
{
    int zostalo = 0;
    for (long long a = 0; a < 1000000000; a++)
    {
        programy = dzien16a(ruchy, programy);
        if (programy == "abcdefghijklmnop")
        {
            int iter = a;
            //std::cout << iter << std::endl;
            zostalo = 1000000000 % (iter + 1);
            // std::cout << zostalo << std::endl;
            // std::cout << programy << std::endl;
            for (int i = 0; i < zostalo; i++)
            {
                programy = dzien16a(ruchy, programy);
            }
            break;
        }

    }
    return programy;
}

int main()
{
    std::string   programy = "abcdefghijklmnop";
    std::string   ruchy;
    std::ifstream file("C:\\moje\\studia\\C++\\Zejsciówki\\projekt2\\data\\taniec.txt"); //tutaj trzeba zmieniæ na swoj¹ œcie¿kê
    if (!file.is_open())
    {
        std::cout << "Nie mozna otworzyc pliku taniec.txt!" << std::endl;

        return 1;
    }
    std::getline(file, ruchy);
    auto elementy = Taniec(ruchy);
    long long zostalo = 0;
    std::cout << dzien16a(elementy, programy) << std::endl;
    std::cout << dzien16b(elementy, programy) << std::endl;

}
