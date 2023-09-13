# NMR_Processing
Qt Program for processing NMR relaxometer data

Для сборки проекта нужны:
* cmake старше 3.5
* Qt использовался 5.14
* Eigen3 (для матричных операций) устанавалась последняя версия из vcpkg
* Для подключения Eigen, нужно в CMakeLists.txt заменить путь до vcpkg.cmake, в 11 строкe
* Также у меня оно не завелось из под g++, но хорошо работает с Visual Studio Community 2022

# Установка зависимостей

## Cmake
Cmake можно скачать [отсюда](https://cmake.org/download/)

## Qt 
Я использовал пиратский установщик (потому что официальный в россии не работает), вроде бы [вот здесь](https://cybersoft.ru/razrabotka/redaktory/208-qt.html) можно скачать

## Eigen
Устанавливался через vcpkg
```
vcpkg install eigen3[core]:x64-windows
```
После установки нужно сделать integrate install, чтобы vcpkg скопировал заголовки и файлы библиотеки куда нужно, а также прописал себе в vcpkg.cmake нужную конфигурацию

Делается это как:
```
vcpkg integrate install
```
После этого vcpkg также любезно должен выдать строчку:
CMake projects should use: "-DCMAKE_TOOLCHAIN_FILE=Путь/До/Нужного/Нам/vcpkg.cmake"

Путь из этой строчки нужно скопировать и вставить вместо 
> D:/Development/vcpkg/vcpkg/scripts/buildsystems/vcpkg.cmake

# Сборка

Чтобы собрать проект, склонируйте репозиторий:
```
git clone https://github.com/Dm1stry/NMR_Processing.git
```

Затем перейдите в репозиторий
```
cd NMR_Processing
```

Создайте папку, где будет собираться проект и перейдите в нее
```
mkdir build
cd build
```

Запустите из неё cmake, чтобы сгененрировать файлы проекта:
```
cmake ..
```

И затем когда CMake сгенерирует файлы проекта, соберите проект командой:
```
cmake --build .
```

