OBJS=galaxy.o vec3.o body.o node.o constants.o
SDL=$(shell sdl2-config --static-libs --cflags)
APP=Galaxy.exe

$(APP) : $(OBJS)
	g++ -o $(APP) $(OBJS) $(SDL)
	
%.o : %.cpp
	g++ $< -c

clean:
	rm $(OBJS)
	rm $(APP)
