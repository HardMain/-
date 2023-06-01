#include "Graph.h"

void Graph::visualGraph(RenderWindow& w)
{
    CircleShape circle(80.f / pow(1.1, size));
    circle.setOrigin(circle.getRadius(), circle.getRadius());
    circle.setFillColor(Color(41, 199, 199));
    circle.setOutlineColor(Color(255, 0, 128));
    circle.setOutlineThickness(3);

    Font fnt;
    fnt.loadFromFile("C:/Windows/Fonts/Arial.ttf");

    int current = 0;
    int temp = size;
    vector<pair<float, float>> v_coords(numVertices);

    for (size_t i = 0; i < temp; ++i)
    {
        if (existVertex[i] != -1)
        {
            v_coords[i] = make_pair(w.getView().getCenter().x + LEN * sin((360.f / size * (float)current + 180) / 180.f * PI), w.getView().getCenter().y + LEN * cos((360.f / size * (float)current + 180) / 180.f * PI));
            ++current;
        }
        else
            ++temp;
    }

    for (size_t i = 0; i < numVertices; ++i)
    {
        for (size_t j = i + 1; j < numVertices; ++j)
        {
            RectangleShape line;
            line.setFillColor(Color(255, 0, 128));
            if (i != j && matrix[i][j] != 100000)
                if (matrix[i][j] == matrix[j][i])
                {
                    Text txt2(to_string(matrix[i][j]), fnt, 35 / pow(1.1, size));
                    txt2.setOrigin(txt2.getLocalBounds().width / 2.f, txt2.getLocalBounds().height);
                    txt2.setFillColor(Color(44, 105, 22));
                    txt2.setOutlineThickness(4);
                    txt2.setOutlineColor(Color(255, 128, 255));

                    line.setSize(Vector2f(2, sqrt(pow(v_coords[i].first - v_coords[j].first, 2) + pow(v_coords[i].second - v_coords[j].second, 2))));
                    line.setPosition(v_coords[i].first, v_coords[i].second);

                    float k = 1.f / 6.3 * pow(float(i + j), 1 / 2);
                    if (j >= (numVertices) / 2)
                        k *= 2.63;
                    else
                        k *= 1.97;

                    if (v_coords[i].first - v_coords[j].first < 0 && (int)(v_coords[i].second - v_coords[j].second) == 0)
                    {
                        line.rotate(180 + 90 - atan(abs(v_coords[i].second - v_coords[j].second) / abs((float)(v_coords[i].first - v_coords[j].first))) * 180 / PI);
                        txt2.setPosition(line.getPosition().x + line.getSize().y * k, line.getPosition().y);
                        txt2.setRotation(0);
                    }
                    else if ((int)(v_coords[i].first - v_coords[j].first) == 0 && v_coords[i].second - v_coords[j].second < 0)
                    {
                        line.rotate(90 - atan(abs(v_coords[i].second - v_coords[j].second) / abs((float)(v_coords[i].first - v_coords[j].first))) * 180 / PI);
                        txt2.setPosition(line.getPosition().x, line.getPosition().y + line.getSize().y * k);
                        txt2.setRotation(-90);
                    }
                    else if (v_coords[i].first - v_coords[j].first > 0 && v_coords[i].second - v_coords[j].second < 0)
                    {
                        line.rotate(90 - atan(abs(v_coords[i].second - v_coords[j].second) / abs((float)(v_coords[i].first - v_coords[j].first))) * 180 / PI);
                        txt2.setPosition(line.getPosition().x - abs(v_coords[i].first - v_coords[j].first) * k, line.getPosition().y + abs(v_coords[i].second - v_coords[j].second) * k);
                        txt2.setRotation(-90 + line.getRotation());
                    }
                    else if (v_coords[i].first - v_coords[j].first < 0 && v_coords[i].second - v_coords[j].second < 0)
                    {
                        line.rotate(-(90 - atan(abs(v_coords[i].second - v_coords[j].second) / abs((float)(v_coords[i].first - v_coords[j].first))) * 180 / PI));
                        txt2.setPosition(line.getPosition().x + abs(v_coords[i].first - v_coords[j].first) * k, line.getPosition().y + abs(v_coords[i].second - v_coords[j].second) * k);
                        txt2.setRotation(90 + line.getRotation());
                    }
                    else if (v_coords[i].first - v_coords[j].first < 0 && v_coords[i].second - v_coords[j].second > 0)
                    {
                        line.rotate(180 + 90 - atan(abs(v_coords[i].second - v_coords[j].second) / abs((float)(v_coords[i].first - v_coords[j].first))) * 180 / PI);
                        txt2.setPosition(line.getPosition().x + abs(v_coords[i].first - v_coords[j].first) * k, line.getPosition().y - abs(v_coords[i].second - v_coords[j].second) * k);
                        txt2.setRotation(90 + line.getRotation());
                    }
                    else if (v_coords[i].first - v_coords[j].first > 0 && v_coords[i].second - v_coords[j].second > 0)
                    {
                        line.rotate(90 + atan(abs(v_coords[i].second - v_coords[j].second) / abs((float)(v_coords[i].first - v_coords[j].first))) * 180 / PI);
                        txt2.setPosition(line.getPosition().x - abs(v_coords[i].first - v_coords[j].first) * k, line.getPosition().y - abs(v_coords[i].second - v_coords[j].second) * k);
                        txt2.setRotation(-90 + line.getRotation());
                    }

                    w.draw(line);
                    w.draw(txt2);
                }
        }

        if (existVertex[i] != -1)
        {
            circle.setPosition(v_coords[i].first, v_coords[i].second);

            Text txt(to_string(i), fnt, 80 / pow(1.1, size));
            txt.setOrigin(txt.getLocalBounds().width / 2.f, txt.getLocalBounds().height);
            txt.setFillColor(Color::Yellow);
            txt.setPosition(circle.getPosition().x - 1, circle.getPosition().y + 4);

            w.draw(circle);
            w.draw(txt);
        }
    }

    RectangleShape rect;
    rect.setFillColor(Color(215, 215, 215));
    rect.setOutlineColor(Color::Black);
    rect.setOutlineThickness(2);

    vector<String> button_text
    {
        L"Добавить вершину",
        L"Добавить ребро",
        L"Удалить вершину",
        L"Удалить ребро",
        L"Salesman"
    };

    for (size_t i = 0; i < 5; i++)
    {
        Text txt(button_text[i], fnt, 24);

        rect.setSize(Vector2f(235, 50));
        button_coords[i].x = 15; button_coords[i].y = 15 + 100 * i;
        rect.setPosition(button_coords[i]);
        
        txt.setFillColor(Color(5,16,218));
        txt.setOrigin(txt.getLocalBounds().width / 2.f, txt.getGlobalBounds().height / 2.f);
        txt.setPosition(rect.getPosition().x + rect.getLocalBounds().width / 2.f, rect.getPosition().y + rect.getGlobalBounds().height / 2.f - 5);

        w.draw(rect);
        w.draw(txt);

    }
}

void Graph::EventMouseButtonPressed(Vector2f ButtonPressedCoords, RenderWindow &w)
{
    Font fnt;
    fnt.loadFromFile("C:/Windows/Fonts/Arial.ttf");

    RenderWindow window;
    RectangleShape rect;
    Text txt;
    Text txt2;
    Text txt3;

    for (size_t i = 0; i < 5; i++)
        if (this->button_coords[i].x <= ButtonPressedCoords.x && this->button_coords[i].x + 235 >= ButtonPressedCoords.x && this->button_coords[i].y <= ButtonPressedCoords.y && this->button_coords[i].y + 50 >= ButtonPressedCoords.y)
            switch (i)
            {
            case 0:
                addVertex();
                break;
            case 1:
            {
                window.create(VideoMode(160, 60), "DeleteVertex", Style::None);
                window.setPosition(Vector2i(w.getView().getCenter().x - window.getView().getCenter().x, w.getView().getCenter().y - window.getView().getCenter().y));

                rect.setSize(Vector2f(150, 50));
                rect.setFillColor(Color::White);
                rect.setOutlineColor(Color::Black);
                rect.setOutlineThickness(2);
                rect.setPosition(5, 5);

                int FV = -1, SV = -1, weight = 0;
                int count = 0;

                txt.setString(L"Вершина 1: ");
                txt.setCharacterSize(20);
                txt.setFont(fnt);
                txt.setOrigin(0, txt.getLocalBounds().height / 2.f);
                txt.setPosition(10, rect.getLocalBounds().height / 2.f);
                txt.setFillColor(Color::Red);

                string inputText;
                Text text;
                text.setFont(fnt);
                text.setCharacterSize(20);
                text.setFillColor(Color::Red);
                text.setOrigin(txt.getLocalBounds().height / 2.f, txt.getLocalBounds().height / 2.f);
                text.setPosition(txt.getPosition().x + txt.getLocalBounds().width + 10, txt.getPosition().y);

                while (window.isOpen())
                {
                    Event event;
                    while (window.pollEvent(event))
                    {
                        if (event.type == sf::Event::TextEntered)
                        {
                            if (event.text.unicode == '\r') //enter
                            {
                                if (inputText == "")
                                    window.close();
                                else if (count == 0)
                                {
                                    FV = stoi(inputText);
                                    inputText.clear();
                                    ++count;
                                    txt.setString(L"Вершина 2: ");
                                    text.setPosition(txt.getPosition().x + txt.getLocalBounds().width + 10, txt.getPosition().y);
                                }
                                else if (count == 1)
                                {
                                    SV = stoi(inputText);
                                    inputText.clear();
                                    ++count;
                                    txt.setString(L"Вес: ");
                                    text.setPosition(txt.getPosition().x + txt.getLocalBounds().width + 10, txt.getPosition().y);
                                }
                                else if (count == 2)
                                {
                                    weight = stoi(inputText);
                                    inputText.clear();
                                    window.close();
                                }
                            }
                            else if (event.text.unicode == 8 && inputText.size() != 0) //backspace
                                inputText.pop_back();
                            else if (event.text.unicode < 128 && event.text.unicode != 8)
                                inputText += static_cast<char>(event.text.unicode);

                            text.setString(inputText);
                        }
                    }
                    window.clear(Color::Yellow);
                    window.draw(rect);
                    window.draw(txt);
                    window.draw(text);
                    window.display();
                }
                addEdge(FV, SV, weight);

                break;
            }
            case 2:
            {
                window.create(VideoMode(225, 60), "DeleteVertex", Style::None);
                window.setPosition(Vector2i(w.getView().getCenter().x - window.getView().getCenter().x, w.getView().getCenter().y - window.getView().getCenter().y));

                rect.setSize(Vector2f(215, 50));
                rect.setFillColor(Color::White);
                rect.setOutlineColor(Color::Black);
                rect.setOutlineThickness(2);
                rect.setPosition(5, 5);

                txt.setString(L"Номер вершины: ");
                txt.setCharacterSize(20);
                txt.setFont(fnt);
                txt.setOrigin(0, txt.getLocalBounds().height / 2.f);
                txt.setPosition(10, rect.getLocalBounds().height / 2.f);
                txt.setFillColor(Color::Red);

                string inputText;
                Text text;
                text.setFont(fnt);
                text.setCharacterSize(20);
                text.setFillColor(Color::Red);
                text.setOrigin(txt.getLocalBounds().height / 2.f, txt.getLocalBounds().height / 2.f);
                text.setPosition(txt.getPosition().x + txt.getLocalBounds().width + 10, txt.getPosition().y);

                while (window.isOpen())
                {
                    Event event;
                    while (window.pollEvent(event))
                    {
                        if (event.type == sf::Event::TextEntered)
                        {
                            if (event.text.unicode == '\r') //enter
                                window.close();
                            else if (event.text.unicode == 8 && inputText.size() != 0) //backspace
                                inputText.pop_back();
                            else if (event.text.unicode < 128 && event.text.unicode != 8)
                                inputText += static_cast<char>(event.text.unicode);

                            text.setString(inputText);
                        }
                    }
                    window.clear(Color::Yellow);
                    window.draw(rect);
                    window.draw(txt);
                    window.draw(text);
                    window.display();
                }

                if (inputText != "")
                    delVertex(stoi(inputText));
                break;
            }
            case 3:
            {
                window.create(VideoMode(160, 60), "DeleteVertex", Style::None);
                window.setPosition(Vector2i(w.getView().getCenter().x - window.getView().getCenter().x, w.getView().getCenter().y - window.getView().getCenter().y));

                rect.setSize(Vector2f(150, 50));
                rect.setFillColor(Color::White);
                rect.setOutlineColor(Color::Black);
                rect.setOutlineThickness(2);
                rect.setPosition(5, 5);

                int FV = -1, SV = -1;
                int count = 0;

                txt.setString(L"Вершина 1: ");
                txt.setCharacterSize(20);
                txt.setFont(fnt);
                txt.setOrigin(0, txt.getLocalBounds().height / 2.f);
                txt.setPosition(10, rect.getLocalBounds().height / 2.f);
                txt.setFillColor(Color::Red);

                string inputText;
                Text text;
                text.setFont(fnt);
                text.setCharacterSize(20);
                text.setFillColor(Color::Red);
                text.setOrigin(txt.getLocalBounds().height / 2.f, txt.getLocalBounds().height / 2.f);
                text.setPosition(txt.getPosition().x + txt.getLocalBounds().width + 10, txt.getPosition().y);

                while (window.isOpen())
                {
                    Event event;
                    while (window.pollEvent(event))
                    {
                        if (event.type == sf::Event::TextEntered)
                        {
                            if (event.text.unicode == '\r') //enter
                            {
                                if (inputText == "")
                                    window.close();
                                else if (count == 0)
                                {
                                    FV = stoi(inputText);
                                    inputText.clear();
                                    ++count;
                                    txt.setString(L"Вершина 2: ");
                                    text.setPosition(txt.getPosition().x + txt.getLocalBounds().width + 10, txt.getPosition().y);
                                }
                                else if (count == 1)
                                {
                                    SV = stoi(inputText);
                                    inputText.clear();
                                    window.close();
                                }
                            }
                            else if (event.text.unicode == 8 && inputText.size() != 0) //backspace
                                inputText.pop_back();
                            else if (event.text.unicode < 128 && event.text.unicode != 8)
                                inputText += static_cast<char>(event.text.unicode);

                            text.setString(inputText);
                        }
                    }
                    window.clear(Color::Yellow);
                    window.draw(rect);
                    window.draw(txt);
                    window.draw(text);
                    window.display();
                }
                delEdge(FV, SV);
                break;
            }
            case 4:
            {
                int len_way = 0;
                String wayS = "";

                Salesman(len_way, matrix, wayS);

                window.create(VideoMode(200 + size * 41, 90), "DeleteVertex", Style::None);
                window.setPosition(Vector2i(w.getView().getCenter().x - window.getView().getCenter().x, w.getView().getCenter().y - window.getView().getCenter().y));

                rect.setSize(Vector2f(window.getView().getSize().x - 10, window.getView().getSize().y - 10));
                rect.setFillColor(Color::White);
                rect.setOutlineColor(Color::Black);
                rect.setOutlineThickness(2);
                rect.setPosition(5, 5);

                txt.setString(L"Начальная вершина пути: ");
                txt.setCharacterSize(20);
                txt.setFont(fnt);
                txt.setOrigin(0, txt.getLocalBounds().height / 2.f);
                txt.setPosition(10, window.getView().getCenter().y);
                txt.setFillColor(Color::Red);

                txt2.setCharacterSize(20);
                txt2.setFont(fnt);
                txt2.setOrigin(0, txt.getLocalBounds().height / 2.f);
                txt2.setPosition(10, rect.getLocalBounds().height / 2.f + 20);
                txt2.setFillColor(Color::Red);

                Text txt4;
                txt4.setCharacterSize(20);
                txt4.setFont(fnt);
                txt4.setOrigin(0, txt.getLocalBounds().height / 2.f);
                txt4.setFillColor(Color::Red);

                txt3.setCharacterSize(20);
                txt3.setFont(fnt);
                txt3.setOrigin(0, txt.getLocalBounds().height / 2.f);
                txt3.setFillColor(Color::Red);

                string inputText;
                Text text;
                text.setFont(fnt);
                text.setCharacterSize(20);
                text.setFillColor(Color::Red);
                text.setOrigin(txt.getLocalBounds().height / 2.f, txt.getLocalBounds().height / 2.f);
                text.setPosition(txt.getPosition().x + txt.getLocalBounds().width + 10, txt.getPosition().y);

                int vertex;

                while (window.isOpen())
                {
                    Event event;
                    while (window.pollEvent(event))
                    {
                        if (event.type == sf::Event::TextEntered)
                        {
                            if (event.text.unicode == '\r') //enter
                            {
                                if (inputText == "" || len_way == 0)
                                    window.close();
                                else
                                {
                                    txt.setPosition(10, 20);
                                    txt.setString(L"Длина пути: ");

                                    txt2.setString(L"Маршрут: ");

                                    txt3.setPosition(txt.getGlobalBounds().width + 10, 20);
                                    txt3.setString(to_string(len_way));

                                    int startCity = stoi(inputText);
                                    if (startCity < 0 || startCity >= numVertices || existVertex[startCity] == -1)
                                    {
                                        cout << "Город введен некорректно!\n";
                                        window.close();
                                        return;
                                    }

                                    int currentCity = startCity;
                                    wayS += to_string(startCity);
                                    currentCity = way[currentCity];
                                    while (currentCity != startCity)
                                    {
                                        wayS += " -> " + to_string(currentCity);
                                        currentCity = way[currentCity];
                                    }
                                    wayS += " -> " + to_string(startCity);

                                    txt4.setPosition(txt2.getLocalBounds().width + 10, rect.getLocalBounds().height / 2.f + 20);
                                    txt4.setString(wayS);

                                    inputText.clear();
                                }
                            }
                            else if (event.text.unicode == 8 && inputText.size() != 0) //backspace
                                inputText.pop_back();
                            else if (event.text.unicode < 128 && event.text.unicode != 8)
                                inputText += static_cast<char>(event.text.unicode);

                            text.setString(inputText);
                        }
                    }
                    window.clear(Color::Yellow);
                    window.draw(rect);
                    window.draw(txt);
                    window.draw(txt2);
                    window.draw(txt3);
                    window.draw(txt4);
                    window.draw(text);
                    window.display();
                }
                way.clear();
                break;
            }
                break;
            default:
                break;
            }
}


