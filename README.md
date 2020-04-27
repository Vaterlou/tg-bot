# Dependencies

* Boost 1.70
* libpqxx	
* openssl

# Compiling

```
git clone https://git.list.family/list/pq-bot
cd pq-bot
mkdir build
cd build
cmake ..
# use "make -j N" for N CPU cores for faster compiling (may require more RAM)
make
```

# Environment variables

* TLG_API_HOST
* TLG_BOT_API_TOKEN 
* TLG_CHAT_ID
* PG_DB_HOST
* PG_DB_PORT
* PG_DB_NAME
* PG_DB_USR
* PG_DB_PWD

# Running

Run example:

```
./pq-bot
```
