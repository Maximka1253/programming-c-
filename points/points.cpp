#include <iostream>
#include <cmath>
using namespace std;

const short MAXNUM = 12;                  //максимальное количество пар 

int dotnum;                             //количество соединений
double redX[MAXNUM], redY[MAXNUM];      //координаты красных точек
double blueX[MAXNUM], blueY[MAXNUM];    //координаты синих точек
bool used[MAXNUM];                      //состояние точки (использована или нет)
double best = INFINITY;                 //лучшее расстояние до точки

double dist(int i, int j){                  //функция подсчета расстояния между точками
    double distX = redX[i] - blueX[j];
    double distY = redY[i] - blueY[j];
    return sqrt(distX*distX + distY*distY); 
}

void mindist(int cnt, double current){  //функция для нахождения минимальной суммы расстояний
    if (current >= best) return;        //отсечение лучшего варианта

    if (cnt == dotnum) {                //если все красные уже соеденены
        best = current;
        return;
    }
    
    for (int i = 0; i < dotnum; i++)   //перебор остальных вариантов
    {
        if (!used[i])
        {
            used[i] = true;
            mindist(cnt+1, current + dist(cnt, i));
            used[i] = false;
        }   
    } 
}

int main(){
    int dotcnt;
    cout << "Введите чётное количество точек в количестве не более 24: " << endl;
    cin >> dotcnt;
    if (dotcnt % 2 != 0 || dotcnt>24)
    {
        throw range_error("Число должно быть чётным и меньше 24");
    }
    
    short num = 1;
    int redcnt = 0, bluecnt = 0;
    cout << "Вводите параметры каждой точки в формате: r/b * *  (количество красных и синих точек должно совпадать):" << endl;
    for (int i = 0; i < dotcnt; i++)
    {
        cout << num << "-я точка:" << endl;
        num++;
        char color;
        double x, y;
        cin >> color >> x >> y;        
        if (color == 'r')
        {
            redX[redcnt] = x;
            redY[redcnt] = y;
            redcnt++;
        }
        else if (color == 'b')
        {
            blueX[bluecnt] = x;
            blueY[bluecnt] = y;
            bluecnt++;
        }
        else throw range_error("Цвет должен быть в формате r или b");
    }
    
    if (redcnt != bluecnt) {
    throw range_error("Количество красных и синих точек должно совпадать");
    }

    dotnum = redcnt;

    for (int i = 0; i < dotnum; i++)
        used[i] = false;
    
    mindist(0, 0.0);

    cout << "Минимальное расстояние для соединения точек: " << best << endl;
    return 0;
}