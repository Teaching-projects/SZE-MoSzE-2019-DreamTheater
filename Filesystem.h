#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include "Directory.h"
#include <list>
#include <vector>
using namespace std;
    
    
class FileSystem
{
private:
    list <Directory*> listOfFolders;
    Directory* root;

public:
    /**
     * @brief Beállítja a gyökért és a jelengi mappát
    */
    FileSystem();
    /**
     * @brief Felszabadítja a létrehozott mappák listáját és a gyökért
    */
    ~FileSystem();
    /**
     * @brief Betölti egy fájl tartalmát, ha nem létezik létre hoz egyet
     * @param string Egy létező/nem létező fájl
    */
    bool loadFile(string);
    /**
     * @brief Segítségével a tudunk végig menni a mappákon a cd fgv segítségével
     * @param string Az útvonal amin végigszeretnénk haladni absolute/relative path is lehet
     * @param bool Eldönti, hogy levágjuk utolsó string a vectorból
     * @param bool Eldönti, hogy visszalépjünk-e ahonnan kezdtük a lépkedést
     */
    string followPath(string, bool, bool);
    /**
     * @brief Létező fájlokat/mappákat tudunk mozgatni
     * @param string A path a file/mappához amit mozgatni szeretnénk
     * @param string A cél mappához vezető útvonal
     */
    void mv(string ,string);
    /**
     * @brief Egy létező/nem létező fájlnak tudunk tartalmat adni
     * @param string Megadjuk a fájl tartalmát
     * @param string Megadjuk a fájl nevét
     */
    void echo(string, string);
    /**
     * @brief Mappa törlés
     * @param string A törölni kivánt mappához vezető útvonal
     */
    void rm(string);
    /**
     *@brief Filelétrehozás
     *@param string A nem létező fájl neve
     *@warning Nem létező fájl esetén hibaüzenet
     */
    void touch(string);
    /**
     *@brief Mappa létrehozás
     *@param string A nem létező mappa neve
     *@warning Nem létező mappa esetén hibaüzenet
     */
    void mkdir(string);
    /**
     * @brief A jelenlegi mappa tartalmának listázása
     */
    void ls();
    /**
     *@brief Lépés a következő létező mappába
     *@param string A létező mappa neve
     *@warning Nem létező mappa esetén hibaüzenet
     */ 
    bool cd(string);
    /**
     *@brief A beírt command alaki ellenőrzése
     *@param string A meghívni kivánt command
     *@param vector A beírt argumentumok egy vectorban
     *@param bool Ha a user virtuális fájlrendszert alkalmazza ne ellenőrizzen
     */ 
    bool inputCheck(string , vector<string>, bool );
    /**
     * @brief A tartokozási helyünket itt tároljuk, melyik mappában vagyunk épp
     */ 
    Directory* currentDir;
    void start();
    /**
     * @brief Megnézi, hogy van e ilyen file az aktuális mappában
     * @param string A fájl neve
     */ 
    bool hasFile(string);
        /**
     * @brief Megnézi, hogy van e ilyen mappa az aktuális mappában
     * @param string A mappa neve
     */ 
    bool hasDir(string);
    /**
     * @brief Feldolgozza az útvonal stringet
     * @param string Az útovonal string
     * @return Visszaadja a szétszedett útvonalat sorrendben
     */ 
    vector<string> processPath(string);
};

#endif // FILESYSTEM_H