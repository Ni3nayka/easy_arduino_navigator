#define NAVIGATOR_QUANTITY_POINT 25 // количество точек (квадратиков) в лабиринте, нужно только если надо возвращаться назад по оптимальному пути, если нет, можно закоментировать (удалить). Здесь лабиринт 5х5, следовательно количество точек 25

#include <easy_arduino_navigator.h> // подключаем бибилиотеку

// создаем объект навигатора, который будет нас направлять 
Navigator navigator(NAVIGATOR_RIGHT_ARM_RULE); // NAVIGATOR_RIGHT_ARM_RULE/NAVIGATOR_LEFT_ARM_RULE - изучать лабиринт по правилу правой/левой руки

/* МАНУАЛ:
 *
 * у робота могут быть сследующие направления (север/запад/юг/восток - относительно карты):
 *   N
 *   |
 * W-0-E
 *   |
 *   S
 *  NAVIGATOR_DIR_N // константа направления на север
 *  NAVIGATOR_DIR_W // константа направления на запад
 *  NAVIGATOR_DIR_S // константа направления на юг
 *  NAVIGATOR_DIR_E // константа направления на восток
 *
 * робот находится в системе координат (нулевая точка может быть где угодно, не обязательно в точке старта):
 * ^ y
 * |
 * |
 * +-----> x
 */

void test() { // подпрограмма для вывода данных о положении робота в пространстве
  Serial.print(navigator.get_x()); // координата робота по Х
  Serial.print(" ");
  Serial.print(navigator.get_y()); // координата робота по У
  Serial.print(" ");
  Serial.println(navigator.get_dir()); // направление робота (NAVIGATOR_DIR_N/NAVIGATOR_DIR_W/NAVIGATOR_DIR_S/NAVIGATOR_DIR_E)
}

void move(bool forward_wall, bool side_wall) { // подпрограмма для виртуального теста, получает на вход данные с "виртуальных датчиков"
  if (navigator.this_is_finish()) { // если мы на финише?
    Serial.println("end"); // то все
    return;
  }
  int t = navigator.next_move(forward_wall,side_wall); // спрашиваем у навигатора что делать, и подаем ему на вход наличие стенок (данные с датчиков, 1 - стенка есть (рядом), 0 - стенки нет (рядом))
  // при вызове этой (предыдущей) команды навигатор считает что вы выполните его команду (t) без ошибок
  robot_move(t);
}

void robot_move(int t) { // выполняем роботом заданную команду
  if (t==NAVIGATOR_END) { // если навигатор сказал что мы приехали
    Serial.println("end");
    return;
  }
  if (t==NAVIGATOR_MOVE_FORWARD) { // если навигатор сказал ехать прямо
    Serial.println("move forvard");
  }
  if (t==NAVIGATOR_MOVE_LEFT) { // если навигатор сказал повернуть налево
    Serial.println("turn left");
  }
  if (t==NAVIGATOR_MOVE_RIGHT) { // если навигатор сказал повернуть направо
    Serial.println("move right");
  }
  if (t==NAVIGATOR_MOVE_RIGHT_AND_FORWARD) { // если навигатор сказал повернуть направо и ПОТОМ ехать прямо 
    Serial.println("turn right");
    Serial.println("move forward");
  }
  if (t==NAVIGATOR_MOVE_LEFT_AND_FORWARD) { // если навигатор сказал повернуть налево и ПОТОМ ехать прямо 
    Serial.println("turn left");
    Serial.println("move forward");
  }
  if (t==NAVIGATOR_ERROR_LONG_ROUTE) { // ошибка - вы где-то ошиблись, из-за чего путь стал длиннее максимально возможного
    Serial.println("error: long route");
  }
}

void setup() {
  Serial.begin(9600);
  
  // задаем точки и направления старта и финиша
  navigator.set_start(0,0,NAVIGATOR_DIR_E); // (X_coordinate, Y_coordinate, direction)
  navigator.set_finish(4,4,NAVIGATOR_DIR_S); // (X_coordinate, Y_coordinate, direction-его можно не задавать)
  
  // прогоняем виртуального "робота" по виртуальному "полю"
  test();
  move(0,1);
  move(0,1);
  move(0,1);
  move(1,1);
  move(1,1);
  move(0,1);
  move(0,0);
  move(0,1);
  move(0,0);
  move(1,1);
  move(1,1);
  move(0,1);
  move(0,0);
  move(0,1);
  move(1,0);
  move(0,1);
  move(1,1);
  move(1,1);
  move(1,1);
  move(1,1);
  move(1,1);
  test();

  // возврат на старт
  while (navigator.this_is_start()==0) { // пока мы не на старте
    int t = navigator.next_move_backward(); // запрашиваем что делать
    robot_move(t); // делаем
  }

}

void loop() {
  
}
