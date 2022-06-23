#ifndef _matrix_h_
#define _matrix_h_

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <locale.h>
#include <conio.h>
#include <fstream>
#include <ctime>
#include <math.h>
#include <iomanip>

using namespace std;

struct Mat
{
    int r; //rows
    int c; //columns
    float **rxc;
    float ***sub;
    string mFile;
};
Mat M1, M2, M3;

void dimensions(Mat *M1, Mat *M2)
{
    int k;
    cout<<"Z przedzia³u [1, 100] podaj wymiar n dwóch macierzy NxN: ";
    do
    {
        cin>>M1->r;
        if(M1->r<1 || M1->r>100)
        {
            cout<<"Nale¿a³o wybraæ liczbê z przedzia³u [1, 100], wybierz ponownie ";
            k=1;
        }
        else
            k=0;
    }while(k==1);

    M1->c=M1->r;
    M2->r=M1->r;
    M2->c=M1->r;

    cout<<"Macierze maj¹ wymiary ["<<M2->r<<", "<<M2->c<<"]."<<endl;
}

float randomFloat(float Min,float Max)
{
    float num;
    float temp;
    if(Min>Max)
    {
        temp=Min;
        Min=Max;
        Max=temp;
    }
    num = Min + static_cast <float> (rand()) /(static_cast <float> (RAND_MAX/(Max-Min)));

    return num;
}

void mFill(string fileName, Mat *M)
{
    ofstream saveFile;
    saveFile.open(fileName.c_str(),ios::out);

    if(saveFile.good())
    {
        float **arr = new float *[M->r];
        for(int i=0; i<M->r; ++i)
            arr[i] = new float[M->c];
        M->rxc = arr;
        int pick, k;

        cout<<"Czy chcesz uzupe³niæ macierz w³asnorêcznie, czy automatycznie uzupe³niæ j¹ losowymi liczbami?"<<endl;
        cout<<"1 - w³asnorêcznie\t2 - automatycznie"<<endl;
        cout<<"Twój wybór: ";

        do
        {
            cin>>pick;
            if(pick==1 || pick==2)
            {
                switch(pick)
                {
                case 1:
                    for(int i=0;i<M->r;i++)
                    {
                        for(int j=0;j<M->c;j++)
                        {
                            cin>>arr[i][j];
                            if(j==0 && j==(M->c-1))
                                saveFile<<"| "<<arr[i][j]<<" |"<<endl;
                            else if(j==0 && j!=(M->c-1))
                                saveFile<<"| "<<arr[i][j]<<", ";
                            else if(j!=0 && j==(M->c-1))
                                saveFile<<arr[i][j]<<" |"<<endl;
                            else
                                saveFile<<arr[i][j]<<", ";
                        }
                    }
                    break;

                case 2:
                    float Min,Max;
                    cout<<"Podaj zakres z jakiego bêd¹ losowane liczby rzeczywiste:"<<endl;
                    cout<<"\tpocz¹tek przedzia³u: ";
                    cin>>Min;
                    cout<<"\tkoniec przedzia³u: ";
                    cin>>Max;
                    for(int i=0;i<M->r;i++)
                    {
                        for(int j=0;j<M->c;j++)
                        {
                            arr[i][j]=randomFloat(Min,Max);
                            if(j==0 && j==(M->c-1))
                                saveFile<<"| "<<arr[i][j]<<" |"<<endl;
                            else if(j==0 && j!=(M->c-1))
                                saveFile<<"| "<<arr[i][j]<<", ";
                            else if(j!=0 && j==(M->c-1))
                                saveFile<<arr[i][j]<<" |"<<endl;
                            else
                                saveFile<<arr[i][j]<<", ";
                        }
                    }
                    break;
                }
                k=0;
            }
            else
            {
                cout<<"Niew³aœciwy wybór, wybierz 1 lub 2: ";
                k=1;
            }
        }while(k!=0);

        saveFile.close();

    }
    else
        cout<<"B³¹d otwarcia pliku."<<endl;
}

void mPrint(string fileName)
{
    ifstream printFile;
    printFile.open(fileName.c_str(),ios::in);

    if(printFile.good())
    {
        string linia;
        while(!printFile.eof())
        {
            getline(printFile,linia);
            cout<<linia<<endl;
        }

        printFile.close();
    }
    else
        cout<<"B³¹d otwarcia pliku."<<endl;
}

void mMulti(string fileMulti, Mat M1, Mat M2, Mat *M3)
{
    ofstream abMulti;
    abMulti.open(fileMulti.c_str(),ios::out);

    if(abMulti.good())
    {
        float s;
        float **arr3 = new float *[M1.r];
        for(int i=0; i<M1.r; ++i)
            arr3[i] = new float [M2.c];
        M3->rxc = arr3;

        /*
        A(M1.r x M1.c)
        B(M2.r x M2.c)
        C = AxB
        C(M1.r x M2.c)
        */

        for(int i=0; i<M1.r; i++)
        {
            for(int j=0; j<M2.c; j++)
            {
                s=0;
                for(int k=0; k<M1.c; k++)
                    s+=(M1.rxc[i][k]*M2.rxc[k][j]);
                arr3[i][j]=s;
            }
        }

        for(int i=0; i<M1.r; i++)
        {
            for(int j=0; j<M2.c; j++)
            {
                if(j==0 && j==(M2.c-1))
                    abMulti<<"| "<<M3->rxc[i][j]<<" |"<<endl;
                else if(j==0 && j!=(M2.c-1))
                    abMulti<<"| "<<M3->rxc[i][j]<<", ";
                else if(j!=0 && j==(M2.c-1))
                    abMulti<<M3->rxc[i][j]<<" |"<<endl;
                else
                    abMulti<<M3->rxc[i][j]<<", ";
            }
        }

        abMulti.close();
    }
    else
        cout<<"B³¹d utworzenia pliku!"<<endl;
}

void partitionNumber(int *n, Mat M)
{
    int repeats;

    if(M.r%2==0 && M.r%3==0)
    {
        cout<<"Aby podzieliæ macierze na NxN bloków podaj liczbê n z przedzia³u [1, 3]: ";
        do
        {
            cin>>*n;

            if(*n>0 && *n<4)
                repeats=0;
            else
                repeats=1;

            if(repeats!=0)
                cout<<"Niepoprawna wartoœæ, podaj n z przedzia³u [1, 3]: ";
        }while(repeats!=0);
    }
    else if(M.r%2==0 && M.r%3!=0)
    {
        cout<<"Aby podzieliæ macierze na NxN bloków podaj liczbê n równ¹ 1 lub 2: ";
        do
        {
            cin>>*n;

            if(*n==1 || *n==2)
                repeats=0;
            else
                repeats=1;

            if(repeats!=0)
                cout<<"Niepoprawna wartoœæ, podaj n równ¹ 1 lub 2: ";
        }while(repeats!=0);
    }
    else if(M.r%2!=0 && M.r%3==0)
    {
        cout<<"Aby podzieliæ macierze na NxN bloków podaj liczbê n równ¹ 1 lub 3: ";
        do
        {
            cin>>*n;

            if(*n==1 || *n==3)
                repeats=0;
            else
                repeats=1;

            if(repeats!=0)
                cout<<"Niepoprawna wartoœæ, podaj n równ¹ 1 lub 3: ";
        }while(repeats!=0);
    }
    else
    {
        cout<<"Przy takich wymiarach macierzy dopuszczalne s¹ tylko macierze jednoblokowe! ";
        *n=1;
    }

    cout<<"Macierz bêdzie podzielona na "<<*n<<" bloków wzd³ó¿ i wszerz!"<<endl;
}

void partitioning2n(string fileMulti, Mat *M1, Mat *M2, Mat *M3)
{
    ofstream abMulti;
    abMulti.open(fileMulti.c_str(),ios::out);

    if(abMulti.good())
    {
        int subSize = M1->c/2;
        float s;
        float ***sub1 = new float**[4];
        float ***sub2 = new float**[4];
        float ***sub3 = new float**[4];
        for(int i=0; i<4; i++)
        {
            sub1[i] = new float*[subSize];
            sub2[i] = new float*[subSize];
            sub3[i] = new float*[subSize];
            for(int j=0; j<subSize; j++)
            {
                sub1[i][j] = new float[subSize];
                sub2[i][j] = new float[subSize];
                sub3[i][j] = new float[subSize];
            }
        }
        M1->sub = sub1;
        M2->sub = sub2;
        M3->sub = sub3;

        for(int i=0; i<subSize; i++)
        {
            for(int j=0; j<subSize; j++)
            {
                sub1[0][i][j] = M1->rxc[i][j];
                sub1[1][i][j] = M1->rxc[i][j + subSize];
                sub1[2][i][j] = M1->rxc[i + subSize][j];
                sub1[3][i][j] = M1->rxc[i + subSize][j + subSize];

                sub2[0][i][j] = M2->rxc[i][j];
                sub2[1][i][j] = M2->rxc[i][j + subSize];
                sub2[2][i][j] = M2->rxc[i + subSize][j];
                sub2[3][i][j] = M2->rxc[i + subSize][j + subSize];
            }
        }

        for(int z=0; z<4; z++)
        {

        for(int i=0; i<subSize; i++)
        {
            for(int j=0; j<subSize; j++)
            {
                cout<<sub1[z][i][j]<<", ";

            }
        }
        }

        /*float **arr3 = new float *[subSize];
        for(int i=0; i<subSize; ++i)
            arr3[i] = new float [subSize];
        M3->rxc = arr3;

        //1.1
        for(int z=0; z<4; z++)
        {
            for(int i=0; i<subSize; i++)
            {
                for(int j=0; j<subSize; j++)
                {
                    s=0;
                    for(int k=0; k<subSize; k++)
                        s+=(sub1[z][i][k]*sub2[z][k][j]);
                    arr3[i][j]=s;
                    sub3[z][i][j]=arr3[i][j];
                }
            }
        }

        /*
        A11 A12
        A21 A22

        B11 B12
        B21 B22

        //1.2

        for(int k=0; k<4; k++)
        {
            for(int i=0; i<subSize; i++)
            {
                for(int j=0; j<subSize; j++)
                {
                    if(j==0 && j==(subSize-1))
                        cout<<"| "<<M3->sub[k][i][j]<<" |"<<endl;
                    else if(j==0 && j!=(subSize-1))
                        cout<<"| "<<M3->sub[k][i][j]<<", ";
                    else if(j!=0 && j==(subSize-1))
                        cout<<M3->sub[k][i][j]<<" |"<<endl;
                    else
                        cout<<M3->sub[k][i][j]<<", ";
                }
            }
        }*/
        abMulti.close();
    }
    else
        cout<<"B³¹d utworzenia pliku!"<<endl;
}

void partitioning3n(string fileMulti, Mat M1, Mat M2, Mat M3)
{

}

void menu(Mat M1, Mat M2)
{
    setlocale(LC_ALL,"polish");
    srand(time(NULL));

    dimensions(&M1, &M2);
    cout<<"Macierz 1.: "<<endl;
    mFill("save1.txt", &M1);
    mPrint("save1.txt");
    cout<<"\nMacierz 2.: "<<endl;
    mFill("save2.txt", &M2);
    mPrint("save2.txt");

    int n;
    partitionNumber(&n, M1);
    if(n==1)
    {
        cout<<"\nM3 = M1 x M2 = "<<endl;
        mMulti("multiplied.txt", M1, M2, &M3);
        mPrint("multiplied.txt");
    }
    else if(n==2)
    {
        //partitioning2n("multiplied.txt", M1, M2, M3, n);
        partitioning2n("multiplied.txt", &M1, &M2, &M3);
        mPrint("multiplied.txt");
    }
    else
    {
        //partitioning3n("multiplied.txt", M1, M2, M3, n);
    }
}

#endif // _matrix_h_
