#include "Libraries.h"
#include "Graph.h"

int main()
{
    setlocale(LC_ALL, "ru_Rus.UTF-8");
    system("chcp 1251 >> null");

    //int n;
    //cout << "Количество вершин: "; cin >> n;
    Graph graph(0);

    /*graph.addEdge(0, 1, 1);
    graph.addEdge(1, 0, 1);
    graph.addEdge(2, 1, 2);
    graph.addEdge(1, 2, 2);
    graph.addEdge(3, 1, 3);
    graph.addEdge(1, 3, 3);
    graph.addEdge(2, 0, 4);
    graph.addEdge(0, 2, 4);
    graph.addEdge(3, 0, 5);
    graph.addEdge(0, 3, 5);
    graph.addEdge(3, 2, 6);
    graph.addEdge(2, 3, 6);
    graph.addEdge(1, 9, 7);
    graph.addEdge(9, 1, 7);
    graph.addEdge(7, 3, 8);
    graph.addEdge(3, 7, 8);
    graph.addEdge(8, 9, 9);
    graph.addEdge(9, 8, 9);
    graph.addEdge(4, 9, 10);
    graph.addEdge(9, 4, 10);
    graph.addEdge(1, 6, 11);
    graph.addEdge(6, 1, 11);
    graph.addEdge(3, 8, 12);
    graph.addEdge(8, 3, 12);
    graph.addEdge(2, 7, 14);
    graph.addEdge(7, 2, 14);
    graph.addEdge(1, 5, 15);
    graph.addEdge(5, 1, 15);
    graph.addEdge(1, 4, 16);
    graph.addEdge(4, 1, 16);
    graph.addEdge(3, 4, 17);
    graph.addEdge(4, 3, 17);
    graph.addEdge(4, 5, 18);
    graph.addEdge(5, 4, 18);
    graph.addEdge(5, 0, 19);
    graph.addEdge(0, 5, 19);
    graph.addEdge(4, 0, 20);
    graph.addEdge(0, 4, 20);
    graph.addEdge(2, 4, 21);
    graph.addEdge(4, 2, 21);
    graph.addEdge(2, 5, 22);
    graph.addEdge(5, 2, 22);
    graph.addEdge(3, 5, 23);
    graph.addEdge(5, 3, 23);
    graph.addEdge(4, 6, 24);
    graph.addEdge(6, 4, 24);
    graph.addEdge(2, 4, 25);
    graph.addEdge(4, 2, 25);
    graph.addEdge(5, 6, 26);
    graph.addEdge(6, 5, 26);
    graph.addEdge(6, 0, 27);
    graph.addEdge(0, 6, 27);
    graph.addEdge(2, 6, 28);
    graph.addEdge(6, 2, 28);
    graph.addEdge(3, 6, 29);
    graph.addEdge(6, 3, 29);
    graph.addEdge(5, 7, 30);
    graph.addEdge(7, 5, 30);
    graph.addEdge(7, 4, 31);
    graph.addEdge(4, 7, 31);
    graph.addEdge(7, 0, 32);
    graph.addEdge(0, 7, 32);
    graph.addEdge(6, 7, 33);
    graph.addEdge(7, 6, 33);*/

    RenderWindow w(VideoMode(1920,1080),"test");
    w.setFramerateLimit(30);

    Font fnt;
    fnt.loadFromFile("C:/Windows/Fonts/Arial.ttf");

    RectangleShape rect;

    while (w.isOpen())
    {
        Event event;
        Vector2f coords;

        while (w.pollEvent(event))
        {
            if (event.type == Event::Closed())
                w.close();

            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
            {
                coords.x = event.mouseButton.x;
                coords.y = event.mouseButton.y;
            }
            
            vector<Vector2f> button_coords = graph.getButtonCoords();
            Vector2i f = Mouse::getPosition();

            int count = 0;
            for (size_t i = 0; i < 5; i++)
            {
                if (button_coords[i].x <= Mouse::getPosition(w).x && button_coords[i].x + 235 >= Mouse::getPosition(w).x && button_coords[i].y <= Mouse::getPosition(w).y && button_coords[i].y + 50 >= Mouse::getPosition(w).y)
                {
                    rect.setSize(Vector2f(235, 50));
                    rect.setPosition(button_coords[i]);
                    rect.setFillColor(Color(0, 0, 0, 20));

                    count = 0;
                }
                else
                    ++count;
            }
            if (count == 5)
                rect.setFillColor(Color(0, 0, 0, 0));

        }

        w.clear(Color(255,128,255));

        graph.visualGraph(w);
        graph.EventMouseButtonPressed(coords, w);

        w.draw(rect);
        w.display();
    }

    return 0;
}