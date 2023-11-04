# NMR_Processing
Qt Program for processing NMR relaxometer data

Для сборки проекта нужны:
* cmake старше 3.5
* Qt использовался 5.14
* GSL + OpenBLAS (для матричных операций) устанавалась последняя версия из vcpkg
* Для подключения Eigen, нужно в CMakeLists.txt заменить путь до vcpkg.cmake, в 11 строкe
* Также у меня оно не завелось из под g++, но хорошо работает с Visual Studio Community 2022

# Установка зависимостей

## Cmake
Cmake можно скачать [отсюда](https://cmake.org/download/)

## Qt 
Я использовал пиратский установщик (потому что официальный в россии не работает), вроде бы [вот здесь](https://cybersoft.ru/razrabotka/redaktory/208-qt.html) можно скачать

## OpenBLAS, Armadillo и NLopt
Устанавливался через vcpkg
```
vcpkg install armadillo:x64-windows-static
vcpkg install openblas[threads]:x64-windows-static
vcpkg install nlopt:x64-windows-static
```
После установки нужно сделать integrate install, чтобы vcpkg скопировал заголовки и файлы библиотеки куда нужно, а также прописал себе в vcpkg.cmake нужную конфигурацию

Делается это как:
```
vcpkg integrate install
```
После этого vcpkg также любезно должен выдать строчку:
CMake projects should use: "-DCMAKE_TOOLCHAIN_FILE=Путь/До/Нужного/Нам/vcpkg.cmake"

# Сборка

Чтобы собрать проект, создайте папку верхнего уровня, где будет лежать ваш файл конфигурации cmake для использования vcpkg:
```
mkdir NMR_Processing && cd NMR_Processing
```

Cклонируйте туда репозиторий:
```
git clone https://github.com/Dm1stry/NMR_Processing.git
```
Создайте файл CMakeLists.txt в папке верхнего уровня c следующим содержимым:

```
cmake_minimum_required(VERSION 3.10)

set(PROJECT_NAME NMR_Processing)

project(${PROJECT_NAME} VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")

set(VCPKG_TARGET_TRIPLET x64-windows-static)
set(CMAKE_TOOLCHAIN_FILE путь/до/тулчейн/файла/vcpkg.cmake)
include(${CMAKE_TOOLCHAIN_FILE})

add_subdirectory(NMR_Processing)
```
В 4 снизу строке, необходимо подставить путь до тулчейн файла предоставляемого vcpkg, как получить путь написано в разделе **OpenBLAS, Armadillo и NLopt**.

Необходимо создавать cmakelists в директории аерхнего уровня, чтобы после обновления проекта, при его клонировании не приходилось каждый раз вручную заменять путь до тулчейн файла

Создайте папку, где будет собираться проект и перейдите в нее
```
mkdir build && cd build
```

Запустите из неё cmake, чтобы сгененрировать файлы проекта:
```
cmake ..
```

И затем когда CMake сгенерирует файлы проекта, соберите проект командой:
```
cmake --build .
```

