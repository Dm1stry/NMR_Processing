# NMR_Processing
Qt Program for processing NMR relaxometer data

Для сборки проекта нужны:
* cmake старше 3.5
* Qt использовался 5.15
* Eigen3 (для матричных операций) устанавалась последняя версия из vcpkg
* Для подключения Eigen, нужно в CMakeLists.txt заменить путь до vcpkg.cmake, в 11 строкe
* Также у меня оно не завелось из под g++, но хорошо работает с Visual Studio Community 2022

Чтобы собрать проект, склонируйте репозиторий:
```
git clone https://github.com/Dm1stry/NMR_Processing.git
```

Затем перейдите в репозиторий
```
> cd NMR_Processing
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

