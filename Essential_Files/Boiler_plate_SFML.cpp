#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <random>
#include <math.h>

using namespace sf;
using namespace std;
using Closed = Event::Closed;

int main(){
    RenderWindow window(VideoMode({1920,1080}),"Boiler");
    window.setFramerateLimit(144);





    while(window.isOpen()){
        while(auto event = window.pollEvent()){
            if(event->is<Closed> ()){
                window.close();
            }
        }
        

        window.clear(Color::Black);
        window.display();
    }

}