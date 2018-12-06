CC = gcc
OBJS = tcp_client.o main.o
TARGET = cacu
RM = rm -f

$(TARGET):$(OBJS)
	$(CC) -o $(TARGET) $(OBJS)  -lstdc++

$(OBJS):%.o:%.cpp
	$(CC) -c $< -o $@ -lstdc++

clean:
	$(RM) $(TARGET) $(OBJS)