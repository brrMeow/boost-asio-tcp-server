# Boost asio tcp server

Сервер принимает по tcp запрос (имя часового пояса) и отдат ответ (текущее время в этом часовом поясе). В качестве имени часового пояса используется его аббревиатура.

**Клонирование и сборка:**
```bash
git clone https://github.com/brrMeow/boost-asio-tcp-server.git

cd boost-asio-tcp-server/
mkdir build
cd build/

conan install ..
cmake ..
make
```

**Запуск:**
```bash
cd bin/
sudo ./Server
```
**Проверка:**
```bash
telnet localhost 13
Trying 127.0.0.1...
Connected to localhost.
Escape character is '^]'.
BST
Mon Jan 07 15:34:17 GMT 2019
Connection closed by foreign host.
```