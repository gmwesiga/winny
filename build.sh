#!/bin/bash
if [ "$1" == "1" ]; then
g++ -c w_transaction.cxx account.cxx table_data.cxx  color.cxx dataset.cxx algorithms.cxx product_table.cxx product.cxx time.cxx  -std=gnu++11
ar rcs libwinny.a w_transaction.o account.o table_data.o color.o dataset.o algorithms.o product_table.o product.o time.o

elif [ "$1" == "2" ]; then
g++ -c  dataset_view.cxx winny_ui.cxx -I/local/include -std=gnu++11
ar rcs libwinnyFlExt.a dataset_view.o winny_ui.o

else

g++ -c w_transaction.cxx account.cxx table_data.cxx  color.cxx dataset.cxx algorithms.cxx product_table.cxx product.cxx time.cxx  -std=gnu++11
ar rcs libwinny.a w_transaction.o account.o table_data.o color.o dataset.o algorithms.o product_table.o product.o time.o

fi