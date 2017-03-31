#include <iostream>
#include <vector>

using namespace std;

enum class options {Add = 1, Remove, Move, Quit};

options show_menu()
{
    cout << "1. add shape\n"
        "2. remove shape\n"
        "3. move shape\n"
        "4. quit\n";

    int x;
    cin >> x;

    return static_cast<options>(x);
}

class IScreen
{
    public:
        virtual ~IScreen() {};
        virtual void Put_pixel(int x, int y, int c) = 0;
        virtual void Clear() = 0;
        virtual void Show() const = 0;
};

class IShape
{
    int x, y, w, h;
    public:
        virtual ~IShape() {};
        IShape(int x, int y, int w, int h) :
            x(x), y(y), w(w), h(h) {};
        void Move(int nx, int ny)
        {
            x = nx;
            y = ny;
        }
        virtual void Draw(IScreen &scr) const = 0;
        int GetX() const { return x; }
        int GetY() const { return y; }
        int GetW() const { return w; }
        int GetH() const { return h; }
};

class Rectangle: public IShape
{
    public:
        Rectangle(int x, int y, int w, int h) : IShape(x, y, w, h) {};
        void Draw(IScreen &scr) const override
        {
            int x = GetX();
            int y = GetY();
            int w = GetW();
            int h = GetH();
            for (int i = 0; i < w; i++)
            {
                scr.Put_pixel(x + i, y, '*');
                scr.Put_pixel(x + i, y + h - 1, '*');
            }
            for (int i = 1; i < h - 1; i++)
            {
                scr.Put_pixel(x, y + i, '*');
                scr.Put_pixel(x + w - 1, y + i, '*');
            }
        }
};

class Canvas
{
    vector<IShape *> shapes;
    IScreen* scr;

    public:
       Canvas(IScreen* scr) : scr{scr} {}
       void Add(IShape* s)
       {
           shapes.push_back(s);
       }
       void Remove(size_t index)
       {
           delete shapes[index];
           shapes.erase(shapes.begin()+index);
       }
       IShape &operator[](size_t index)
       {
           return *(shapes[index]);
       }
       void Draw()
       {
           scr->Clear();
           for (auto &s : shapes)
           {
               s->Draw(* scr);
           }
           scr->Show();
       }
       ~Canvas()
       {
           delete scr;
           for (auto &s : shapes)
                delete s;
       }
};

class Text_screen : public IScreen
{
    char buffer[20][70];

    public:
        void Clear() override
        {
            for (int i = 0; i < 20; i++)
            {
                for (int j = 0; j < 70; j++)
                {
                    buffer[i][j] = ' ';
                }
            }
        }
        void Show() const override
        {
            for (int i = 0; i < 20; i++)
            {
                for (int j = 0; j < 70; j++)
                {
                    cout << buffer[i][j];
                }
                cout << "\n";
            }
        }
        void Put_pixel(int x, int y, int c)
        {
            if (x >= 70 || y >= 20)
                return;
            buffer[y][x] = c;
        }
};

void process_option(options op, Text_screen cn)
{

}

int main()
{
    /*Text_screen cn; //{80, 25};
    while (true)
    {
        auto op = show_menu();
        if (op == options::Quit)
            return 0;
        process_option(op, cn);
        cn.Show();
    }*/
    Canvas cn { new Text_screen() };
    cn.Add( new Rectangle(6, 6, 10, 4));
    cn.Add( new Rectangle(1, 1, 20, 15));
    cn.Draw();
    int x;
    cin >> x;
    cn[1].Move(20, 9);
    cn.Draw();
}
