clear



g++ -c mainmenu.cpp menugameover.cpp  panel.cpp highscore.cpp triples.cpp tilemap.cpp entitymanager.cpp screenmanager.cpp test.cpp texturemanager.cpp  main.cpp -I/home/stefan/Desktop/SFML/SFML-2.5.1/include/ 


g++ mainmenu.o menugameover.o  panel.o highscore.o triples.o tilemap.o entitymanager.o screenmanager.o test.o texturemanager.o  main.o -o sfml-app -L/home/stefan/Desktop/SFML/SFML-2.5.1/lib -lGL -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system


export LD_LIBRARY_PATH=/home/stefan/Desktop/SFML/SFML-2.5.1/lib/ && ./sfml-app


rm mainmenu.o menugameover.o panel.o highscore.o triples.o tilemap.o entitymanager.o screenmanager.o test.o texturemanager.o  main.o sfml-app
