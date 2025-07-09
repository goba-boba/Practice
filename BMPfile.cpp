#include<iostream>
#include<fstream>  // подключение библиотеки файлового ввода/вывода через потоки
using namespace std;
struct color { unsigned char r; unsigned char g; unsigned char b; };
int main() {
    ifstream fff("1.bmp", ios::binary); //  ios::binary влияет ТОЛЬКО на endl.
    ofstream ggg("rez.bmp", ios::binary);//сюда пишем (поток типа ofstream= output file stream)
    if (!fff) { cout << "No file 1.bmp. Can't open\n"; exit(1); }
    if (!ggg) { cout << "   file rez.bmp. Can't create\n"; exit(1); }

    char buf[100];// куда читать байты
    unsigned char r, g, b; //компоненты цвета
    color c;
    color f;

    int w, h;//надеемся. что тут в int 4 байта
    fff.read((char*)&buf, 18);   //чтение 18 байт заголовка bmp
    ggg.write((char*)&buf, 18);    //запись 18 байт заголовка bmp
    fff.read((char*)&w, 4); cout << "w=" << w;   //чтение width из заголовка bmp
    fff.read((char*)&w, 4); cout << ", h=" << w; //чтение height из заголовка bmp
    w = 256; ggg.write((char*)&w, 4);    //запись width в заголовок bmp (кратно 4, обязательно для нас, чтобы не делать выравнивание)
    h = 256; ggg.write((char*)&h, 4);    //запись height в заголовок bmp
    fff.read((char*)&buf, 28);   //чтение 28 байт заголовка bmp
    ggg.write((char*)&buf, 28);    //запись 28 байт заголовка bmp


    int cr, cg, cb;
    
    // c.r = c.g = 0, c.b = 32;
    cout << "\nenter background color\n";
    cin >> cb;
    cin >> cg;
    cin >> cr;

    c.r = cr; c.g = cg; c.b = cb;

    cout << "enter figure color\n";

    cin >> cb;
    cin >> cg;
    cin >> cr;

    f.r = cr; f.g = cg; f.b = cb;

    int center_h, center_w, size_h, size_w;
    cout << "enter center_h \n";
    cin >> center_h;
    cout << "enter center_w \n";
    cin >> center_w;
    cout << "enter size_h \n";
    cin >> size_h;
    cout << "enter size_w \n";
    cin >> size_w;



    for (int i = 1; i <= h; ++i) {
        //    ++r;g=0;b=0;//диагональный градиент т.к. написали ++r
        for (int j = 1; j <= w; ++j) {
           // ggg.write((char*)&c, sizeof(c));  //запись сразу всего цвета
            if ( (i> center_h-size_h) && (i < center_h + size_h) && (j > center_w - size_w) && (j < center_w + size_w)) {
                ggg.write((char*)&f, sizeof(f));

            }
            else {
                ggg.write((char*)&c, sizeof(c));
            }
            
            // ++c.g;
            /*    ggg.write((char *)&b, sizeof(b));   //запись одной компоненты цвета
                ggg.write((char *)&g, sizeof(g));    //запись одной компоненты цвета
                ggg.write((char *)&r, sizeof(r));    //запись одной компоненты цвета
                ++g;
                */
        }
         // ++c.r; c.g = c.b = 0;
    }

    fff.close();//закрыли файл
    ggg.close();//закрыли файл
    //system("pause");
    return 1;
}
