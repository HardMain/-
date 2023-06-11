# Автоматизированное рабочее место специалиста
## Постановка задачи
Реализовать автоматизированное рабочее место специалиста (АРМ) - товароведа.
Данное АРМ должно выполнять функции:
- Управление событиями.
- Добавление товара в базу данных.
- Редактирование и заполнение склада.
- Автоматический/ручной заказы.
- Ведение статистики продаж.

## Анализ задачи
- Создание приложения выполнялось с использованием кроссплатформенного фреймворка QT на языке с++. С его помощью проводилась работа с базами данны, а также создание пользовательского интерфейса.
- Для добавления товара в базу данных используется запрос на создание таблицы в этой базе с колонками с соответствующими названиями.
- Заполнения склада просходит посредством автоматического/ручного заказа.
- Для ручного заказа предусмотрено окно для ввода информации о товаре, его количестве и дате доставки. Автоматический заказ основан на статистике продаж за последний день.
- Статистика продаж представляет из себя 5 разных таблиц с данными о продаже за последний день/неделю/месяц/полгода/год, каждую из которых можно редактировать и заполнять.

## Тестирование
Тестирование программы представленно в видео на YouTube: [https://youtu.be/06ll9tLrKU0](https://youtu.be/06ll9tLrKU0)

## Сборка и запуск
Для того, чтобы запустить данную программу необходимо скачать zip архив и разархивировать папку ```Part 1 ARM``` в удобное место. 
Далее открыть файл ```.\ARM\ARM.pro``` и скомпилировать программу. Для корректного запуска необходима стандартная поставка QT версии ```QT5.12.12```

## Выполнение программы

<p align="center">
    <img src="https://github.com/HardMain/Creative-Task/blob/main/Part%201%20ARM/ARM/Image/Screenshot_1.png")
/>
</p>
<p align="center">
    Рисунок 1: Главное меню
</p>

<p align="center">
    <img src="https://github.com/HardMain/Creative-Task/blob/main/Part%201%20ARM/ARM/Image/nomen.png")
/>
</p>
<p align="center">
    Рисунок 2: Окно номенклатуры
</p>

<p align="center">
    <img src="https://github.com/HardMain/Creative-Task/blob/main/Part%201%20ARM/ARM/Image/scl.png")
/>
</p>
<p align="center">
    Рисунок 3: Склад
</p>

<p align="center">
    <img src="https://github.com/HardMain/Creative-Task/blob/main/Part%201%20ARM/ARM/Image/nomen.png")
/>
</p>
<p align="center">
    Рисунок 4: Окно выбора заказа
</p>

<p align="center">
    <img src="https://github.com/HardMain/Creative-Task/blob/main/Part%201%20ARM/ARM/Image/ruch.png")
/>
</p>
<p align="center">
    Рисунок 5: Окно ручного заказа
</p>

<p align="center">
    <img src="https://github.com/HardMain/Creative-Task/blob/main/Part%201%20ARM/ARM/Image/stat.png")
/>
</p>
<p align="center">
    Рисунок 6: Статистика продаж
</p>

<p align="center">
    <img src="https://github.com/HardMain/Creative-Task/blob/main/Part%201%20ARM/ARM/Image/diag.png")
/>
</p>
<p align="center">
    Рисунок 7: Диаграмма класса
</p>

## Исходный код

Исходный код представлен в репозитории: https://github.com/der-i/SalesmanProblem-and-ARM/tree/main/ARM
