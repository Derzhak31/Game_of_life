# ***Игра в жизнь***

## *Правила*    

*Для каждой клетки дейтвует правило, если в поле 3х3 (клетка расположена в центре):*    
    - Три живых клетки -> клетка в центре оживает    
    - Две живых клетки -> клетка в центре остается в своем состоянии     
    - Больше трех или меньше -> двух клетка в центре умирает   

___

*Для запуска установить библиотеку **ncurses**, далее в консоле:*    
    **gcc game_of_life.c -o game_of_life.exe -lncursesw**    
    **./game_of_life.exe < <текстовый файл с начальным положением клеток>**    

___

*Кнопки:*   
    **-** - *уменьшить скорость*   
    **+** - *увеличить скорость*   
    **q** - *выйти из интерактивного режима*  
