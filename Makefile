gtkstarter: starter.c 
	gcc -o gtkstarter starter.c `pkg-config --cflags --libs gtk+-3.0` -rdynamic

clean:
	rm gtkstarter

install:
	cp gtkstarter /usr/local/bin/
	mkdir /usr/local/share/gtkstarter
	cp starter.css starter.glade icon.png /usr/local/share/gtkstarter/
	cp gtkstarter.desktop /usr/share/applications/

uninstall:
	rm /usr/local/bin/gtkstarter
	rm -rf /usr/local/share/gtkstarter
	rm /usr/share/applications/gtkstarter.desktop