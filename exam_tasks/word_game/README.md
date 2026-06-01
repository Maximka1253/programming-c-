# Консольная игра «Слова»

Программа реализует консольный вариант игры «Слова» для 2–4 игроков на языке C++.

Игроки по очереди добавляют буквы на квадратное поле 5×5 и составляют слова по соседним клеткам. Переход между буквами возможен только по вертикали и горизонтали. За каждую букву составленного слова игрок получает одно очко.

## Возможности программы

* игра для 2–4 игроков;
* поле размером 5×5;
* стартовое слово размещается в центральной строке;
* проверка слов по словарю `dictionary.txt`;
* запрет повторного использования слов;
* проверка построения слова по соседним клеткам;
* возможность пропустить ход командой `pass`;
* завершение игры при заполнении поля;
* завершение игры после трёх кругов пропусков;
* проверка невозможности дальнейшего хода;
* подсчёт очков;
* запись действий игроков в файл `log.txt`.

## Структура проекта

```text
main.cpp              точка входа в программу
Game.h / Game.cpp     основной игровой цикл
Board.h / Board.cpp   игровое поле
Cell.h / Cell.cpp     клетка игрового поля
Player.h / Player.cpp игрок
Move.h                описание хода
Position.h / .cpp     координаты клетки
Dictionary.h / .cpp   работа со словарём
WordValidator.h / .cpp проверка хода
BoardGraph.h / .cpp   граф соседства клеток
Logger.h / .cpp       запись лога
dictionary.txt        файл со словами
```

## Компиляция

Для компиляции можно использовать команду:

```bash
g++ -std=c++17 -Wall -Wextra -pedantic \
Board.cpp BoardGraph.cpp Cell.cpp Dictionary.cpp Game.cpp Logger.cpp \
main.cpp Player.cpp Position.cpp WordValidator.cpp -o wordgame
```

Или короче:

```bash
g++ -std=c++17 *.cpp -o wordgame
```

## Запуск

```bash
./wordgame
```

## Файл словаря

Перед запуском рядом с программой должен находиться файл:

```text
dictionary.txt
```

В нём каждое слово должно быть записано с новой строки.

Пример:

```text
apple
table
stone
water
green
```

## Правила ввода хода

Во время хода игрок вводит:

1. букву, которую хочет поставить;
2. координаты клетки;
3. слово, которое он составил.

Координаты вводятся числами от `0` до `4`.

Пример хода:

```text
Введите букву или pass для пропуска хода: a
Введите строку и столбец новой буквы: 1 2
Введите составленное слово: apple
```

Чтобы пропустить ход:

```text
pass
```

## Логирование

Все основные действия записываются в файл:

```text
log.txt
```

В лог записываются:

* начало игры;
* список игроков;
* стартовое слово;
* ходы игроков;
* ошибки ходов;
* пропуски;
* итоговые очки;
* победитель.

## Завершение игры

Игра заканчивается, если:

* заполнены все клетки поля;
* игроки сделали три круга пропусков подряд;
* больше невозможно составить ни одного допустимого слова.

## Победитель

Побеждает игрок, набравший больше всего очков.
Если несколько игроков набрали одинаковое максимальное количество очков, объявляется ничья.

## Объектная модель
```mermaid
<mxfile host="app.diagrams.net">
  <diagram name="Страница-1" id="OblurNpZcakYyWiWIkyC">
    <mxGraphModel dx="1489" dy="917" grid="1" gridSize="10" guides="1" tooltips="1" connect="1" arrows="1" fold="1" page="1" pageScale="1" pageWidth="827" pageHeight="1169" math="0" shadow="0">
      <root>
        <mxCell id="0" />
        <mxCell id="1" parent="0" />
        <mxCell id="CtJBt8VR4UTQdoXEWvWE-2" parent="1" style="swimlane;fontStyle=1;align=center;verticalAlign=top;childLayout=stackLayout;horizontal=1;startSize=28.266666666666666;horizontalStack=0;resizeParent=1;resizeParentMax=0;resizeLast=0;collapsible=0;marginBottom=0;fillColor=light-dark(#eeeeee,#1f2020);strokeColor=light-dark(#999999,#cccccc);fontColor=light-dark(#333333,#cccccc);" value="Game" vertex="1">
          <mxGeometry height="428.26666666666665" width="243" x="499" y="60" as="geometry" />
        </mxCell>
        <mxCell id="CtJBt8VR4UTQdoXEWvWE-3" parent="CtJBt8VR4UTQdoXEWvWE-2" style="text;strokeColor=none;fillColor=none;align=left;verticalAlign=top;spacingLeft=4;spacingRight=4;overflow=hidden;rotatable=0;points=[[0,0.5],[1,0.5]];portConstraint=eastwest;" value="-Board board" vertex="1">
          <mxGeometry height="28" width="243" y="28.266666666666666" as="geometry" />
        </mxCell>
        <mxCell id="CtJBt8VR4UTQdoXEWvWE-4" parent="CtJBt8VR4UTQdoXEWvWE-2" style="text;strokeColor=none;fillColor=none;align=left;verticalAlign=top;spacingLeft=4;spacingRight=4;overflow=hidden;rotatable=0;points=[[0,0.5],[1,0.5]];portConstraint=eastwest;" value="-vector players" vertex="1">
          <mxGeometry height="28" width="243" y="56.266666666666666" as="geometry" />
        </mxCell>
        <mxCell id="CtJBt8VR4UTQdoXEWvWE-5" parent="CtJBt8VR4UTQdoXEWvWE-2" style="text;strokeColor=none;fillColor=none;align=left;verticalAlign=top;spacingLeft=4;spacingRight=4;overflow=hidden;rotatable=0;points=[[0,0.5],[1,0.5]];portConstraint=eastwest;" value="-Dictionary dictionary" vertex="1">
          <mxGeometry height="28" width="243" y="84.26666666666667" as="geometry" />
        </mxCell>
        <mxCell id="CtJBt8VR4UTQdoXEWvWE-6" parent="CtJBt8VR4UTQdoXEWvWE-2" style="text;strokeColor=none;fillColor=none;align=left;verticalAlign=top;spacingLeft=4;spacingRight=4;overflow=hidden;rotatable=0;points=[[0,0.5],[1,0.5]];portConstraint=eastwest;" value="-WordValidator validator" vertex="1">
          <mxGeometry height="28" width="243" y="112.26666666666667" as="geometry" />
        </mxCell>
        <mxCell id="CtJBt8VR4UTQdoXEWvWE-7" parent="CtJBt8VR4UTQdoXEWvWE-2" style="text;strokeColor=none;fillColor=none;align=left;verticalAlign=top;spacingLeft=4;spacingRight=4;overflow=hidden;rotatable=0;points=[[0,0.5],[1,0.5]];portConstraint=eastwest;" value="-Logger logger" vertex="1">
          <mxGeometry height="28" width="243" y="140.26666666666665" as="geometry" />
        </mxCell>
        <mxCell id="CtJBt8VR4UTQdoXEWvWE-8" parent="CtJBt8VR4UTQdoXEWvWE-2" style="text;strokeColor=none;fillColor=none;align=left;verticalAlign=top;spacingLeft=4;spacingRight=4;overflow=hidden;rotatable=0;points=[[0,0.5],[1,0.5]];portConstraint=eastwest;" value="-vector usedWords" vertex="1">
          <mxGeometry height="28" width="243" y="168.26666666666665" as="geometry" />
        </mxCell>
        <mxCell id="CtJBt8VR4UTQdoXEWvWE-9" parent="CtJBt8VR4UTQdoXEWvWE-2" style="text;strokeColor=none;fillColor=none;align=left;verticalAlign=top;spacingLeft=4;spacingRight=4;overflow=hidden;rotatable=0;points=[[0,0.5],[1,0.5]];portConstraint=eastwest;" value="-int currentPlayer" vertex="1">
          <mxGeometry height="28" width="243" y="196.26666666666665" as="geometry" />
        </mxCell>
        <mxCell id="CtJBt8VR4UTQdoXEWvWE-10" parent="CtJBt8VR4UTQdoXEWvWE-2" style="text;strokeColor=none;fillColor=none;align=left;verticalAlign=top;spacingLeft=4;spacingRight=4;overflow=hidden;rotatable=0;points=[[0,0.5],[1,0.5]];portConstraint=eastwest;" value="-int passesInRow" vertex="1">
          <mxGeometry height="28" width="243" y="224.26666666666665" as="geometry" />
        </mxCell>
        <mxCell id="CtJBt8VR4UTQdoXEWvWE-11" parent="CtJBt8VR4UTQdoXEWvWE-2" style="line;strokeWidth=1;fillColor=none;align=left;verticalAlign=middle;spacingTop=-1;spacingLeft=3;spacingRight=3;rotatable=0;labelPosition=right;points=[];portConstraint=eastwest;strokeColor=inherit;" vertex="1">
          <mxGeometry height="8" width="243" y="252.26666666666665" as="geometry" />
        </mxCell>
        <mxCell id="CtJBt8VR4UTQdoXEWvWE-12" parent="CtJBt8VR4UTQdoXEWvWE-2" style="text;strokeColor=none;fillColor=none;align=left;verticalAlign=top;spacingLeft=4;spacingRight=4;overflow=hidden;rotatable=0;points=[[0,0.5],[1,0.5]];portConstraint=eastwest;" value="+init()" vertex="1">
          <mxGeometry height="28" width="243" y="260.26666666666665" as="geometry" />
        </mxCell>
        <mxCell id="CtJBt8VR4UTQdoXEWvWE-13" parent="CtJBt8VR4UTQdoXEWvWE-2" style="text;strokeColor=none;fillColor=none;align=left;verticalAlign=top;spacingLeft=4;spacingRight=4;overflow=hidden;rotatable=0;points=[[0,0.5],[1,0.5]];portConstraint=eastwest;" value="+play()" vertex="1">
          <mxGeometry height="28" width="243" y="288.26666666666665" as="geometry" />
        </mxCell>
        <mxCell id="CtJBt8VR4UTQdoXEWvWE-14" parent="CtJBt8VR4UTQdoXEWvWE-2" style="text;strokeColor=none;fillColor=none;align=left;verticalAlign=top;spacingLeft=4;spacingRight=4;overflow=hidden;rotatable=0;points=[[0,0.5],[1,0.5]];portConstraint=eastwest;" value="+inputMove()" vertex="1">
          <mxGeometry height="28" width="243" y="316.26666666666665" as="geometry" />
        </mxCell>
        <mxCell id="CtJBt8VR4UTQdoXEWvWE-15" parent="CtJBt8VR4UTQdoXEWvWE-2" style="text;strokeColor=none;fillColor=none;align=left;verticalAlign=top;spacingLeft=4;spacingRight=4;overflow=hidden;rotatable=0;points=[[0,0.5],[1,0.5]];portConstraint=eastwest;" value="+nextPlayer()" vertex="1">
          <mxGeometry height="28" width="243" y="344.26666666666665" as="geometry" />
        </mxCell>
        <mxCell id="CtJBt8VR4UTQdoXEWvWE-16" parent="CtJBt8VR4UTQdoXEWvWE-2" style="text;strokeColor=none;fillColor=none;align=left;verticalAlign=top;spacingLeft=4;spacingRight=4;overflow=hidden;rotatable=0;points=[[0,0.5],[1,0.5]];portConstraint=eastwest;" value="+isGameOver()" vertex="1">
          <mxGeometry height="28" width="243" y="372.26666666666665" as="geometry" />
        </mxCell>
        <mxCell id="CtJBt8VR4UTQdoXEWvWE-17" parent="CtJBt8VR4UTQdoXEWvWE-2" style="text;strokeColor=none;fillColor=none;align=left;verticalAlign=top;spacingLeft=4;spacingRight=4;overflow=hidden;rotatable=0;points=[[0,0.5],[1,0.5]];portConstraint=eastwest;" value="+printResults()" vertex="1">
          <mxGeometry height="28" width="243" y="400.26666666666665" as="geometry" />
        </mxCell>
        <mxCell id="CtJBt8VR4UTQdoXEWvWE-18" parent="1" style="swimlane;fontStyle=1;align=center;verticalAlign=top;childLayout=stackLayout;horizontal=1;startSize=32;horizontalStack=0;resizeParent=1;resizeParentMax=0;resizeLast=0;collapsible=0;marginBottom=0;fillColor=light-dark(#eeeeee,#1f2020);strokeColor=light-dark(#999999,#cccccc);fontColor=light-dark(#333333,#cccccc);" value="Board" vertex="1">
          <mxGeometry height="264" width="229" x="1225" y="838" as="geometry" />
        </mxCell>
        <mxCell id="CtJBt8VR4UTQdoXEWvWE-19" parent="CtJBt8VR4UTQdoXEWvWE-18" style="text;strokeColor=none;fillColor=none;align=left;verticalAlign=top;spacingLeft=4;spacingRight=4;overflow=hidden;rotatable=0;points=[[0,0.5],[1,0.5]];portConstraint=eastwest;" value="-Cell cells[5][5]" vertex="1">
          <mxGeometry height="32" width="229" y="32" as="geometry" />
        </mxCell>
        <mxCell id="CtJBt8VR4UTQdoXEWvWE-20" parent="CtJBt8VR4UTQdoXEWvWE-18" style="line;strokeWidth=1;fillColor=none;align=left;verticalAlign=middle;spacingTop=-1;spacingLeft=3;spacingRight=3;rotatable=0;labelPosition=right;points=[];portConstraint=eastwest;strokeColor=inherit;" vertex="1">
          <mxGeometry height="8" width="229" y="64" as="geometry" />
        </mxCell>
        <mxCell id="CtJBt8VR4UTQdoXEWvWE-21" parent="CtJBt8VR4UTQdoXEWvWE-18" style="text;strokeColor=none;fillColor=none;align=left;verticalAlign=top;spacingLeft=4;spacingRight=4;overflow=hidden;rotatable=0;points=[[0,0.5],[1,0.5]];portConstraint=eastwest;" value="+initStartWord()" vertex="1">
          <mxGeometry height="32" width="229" y="72" as="geometry" />
        </mxCell>
        <mxCell id="CtJBt8VR4UTQdoXEWvWE-22" parent="CtJBt8VR4UTQdoXEWvWE-18" style="text;strokeColor=none;fillColor=none;align=left;verticalAlign=top;spacingLeft=4;spacingRight=4;overflow=hidden;rotatable=0;points=[[0,0.5],[1,0.5]];portConstraint=eastwest;" value="+setLetter()" vertex="1">
          <mxGeometry height="32" width="229" y="104" as="geometry" />
        </mxCell>
        <mxCell id="CtJBt8VR4UTQdoXEWvWE-23" parent="CtJBt8VR4UTQdoXEWvWE-18" style="text;strokeColor=none;fillColor=none;align=left;verticalAlign=top;spacingLeft=4;spacingRight=4;overflow=hidden;rotatable=0;points=[[0,0.5],[1,0.5]];portConstraint=eastwest;" value="+isEmpty()" vertex="1">
          <mxGeometry height="32" width="229" y="136" as="geometry" />
        </mxCell>
        <mxCell id="CtJBt8VR4UTQdoXEWvWE-24" parent="CtJBt8VR4UTQdoXEWvWE-18" style="text;strokeColor=none;fillColor=none;align=left;verticalAlign=top;spacingLeft=4;spacingRight=4;overflow=hidden;rotatable=0;points=[[0,0.5],[1,0.5]];portConstraint=eastwest;" value="+hasFilledNeighbour()" vertex="1">
          <mxGeometry height="32" width="229" y="168" as="geometry" />
        </mxCell>
        <mxCell id="CtJBt8VR4UTQdoXEWvWE-25" parent="CtJBt8VR4UTQdoXEWvWE-18" style="text;strokeColor=none;fillColor=none;align=left;verticalAlign=top;spacingLeft=4;spacingRight=4;overflow=hidden;rotatable=0;points=[[0,0.5],[1,0.5]];portConstraint=eastwest;" value="+isFull()" vertex="1">
          <mxGeometry height="32" width="229" y="200" as="geometry" />
        </mxCell>
        <mxCell id="CtJBt8VR4UTQdoXEWvWE-26" parent="CtJBt8VR4UTQdoXEWvWE-18" style="text;strokeColor=none;fillColor=none;align=left;verticalAlign=top;spacingLeft=4;spacingRight=4;overflow=hidden;rotatable=0;points=[[0,0.5],[1,0.5]];portConstraint=eastwest;" value="+print()" vertex="1">
          <mxGeometry height="32" width="229" y="232" as="geometry" />
        </mxCell>
        <mxCell id="CtJBt8VR4UTQdoXEWvWE-27" parent="1" style="swimlane;fontStyle=1;align=center;verticalAlign=top;childLayout=stackLayout;horizontal=1;startSize=33.142857142857146;horizontalStack=0;resizeParent=1;resizeParentMax=0;resizeLast=0;collapsible=0;marginBottom=0;fillColor=light-dark(#eeeeee,#1f2020);strokeColor=light-dark(#999999,#cccccc);fontColor=light-dark(#333333,#cccccc);" value="Cell" vertex="1">
          <mxGeometry height="239.14285714285714" width="140" x="1269" y="1200" as="geometry" />
        </mxCell>
        <mxCell id="CtJBt8VR4UTQdoXEWvWE-28" parent="CtJBt8VR4UTQdoXEWvWE-27" style="text;strokeColor=none;fillColor=none;align=left;verticalAlign=top;spacingLeft=4;spacingRight=4;overflow=hidden;rotatable=0;points=[[0,0.5],[1,0.5]];portConstraint=eastwest;" value="-char letter" vertex="1">
          <mxGeometry height="33" width="140" y="33.142857142857146" as="geometry" />
        </mxCell>
        <mxCell id="CtJBt8VR4UTQdoXEWvWE-29" parent="CtJBt8VR4UTQdoXEWvWE-27" style="text;strokeColor=none;fillColor=none;align=left;verticalAlign=top;spacingLeft=4;spacingRight=4;overflow=hidden;rotatable=0;points=[[0,0.5],[1,0.5]];portConstraint=eastwest;" value="-bool empty" vertex="1">
          <mxGeometry height="33" width="140" y="66.14285714285714" as="geometry" />
        </mxCell>
        <mxCell id="CtJBt8VR4UTQdoXEWvWE-30" parent="CtJBt8VR4UTQdoXEWvWE-27" style="line;strokeWidth=1;fillColor=none;align=left;verticalAlign=middle;spacingTop=-1;spacingLeft=3;spacingRight=3;rotatable=0;labelPosition=right;points=[];portConstraint=eastwest;strokeColor=inherit;" vertex="1">
          <mxGeometry height="8" width="140" y="99.14285714285714" as="geometry" />
        </mxCell>
        <mxCell id="CtJBt8VR4UTQdoXEWvWE-31" parent="CtJBt8VR4UTQdoXEWvWE-27" style="text;strokeColor=none;fillColor=none;align=left;verticalAlign=top;spacingLeft=4;spacingRight=4;overflow=hidden;rotatable=0;points=[[0,0.5],[1,0.5]];portConstraint=eastwest;" value="+isEmpty()" vertex="1">
          <mxGeometry height="33" width="140" y="107.14285714285714" as="geometry" />
        </mxCell>
        <mxCell id="CtJBt8VR4UTQdoXEWvWE-32" parent="CtJBt8VR4UTQdoXEWvWE-27" style="text;strokeColor=none;fillColor=none;align=left;verticalAlign=top;spacingLeft=4;spacingRight=4;overflow=hidden;rotatable=0;points=[[0,0.5],[1,0.5]];portConstraint=eastwest;" value="+setLetter()" vertex="1">
          <mxGeometry height="33" width="140" y="140.14285714285714" as="geometry" />
        </mxCell>
        <mxCell id="CtJBt8VR4UTQdoXEWvWE-33" parent="CtJBt8VR4UTQdoXEWvWE-27" style="text;strokeColor=none;fillColor=none;align=left;verticalAlign=top;spacingLeft=4;spacingRight=4;overflow=hidden;rotatable=0;points=[[0,0.5],[1,0.5]];portConstraint=eastwest;" value="+getLetter()" vertex="1">
          <mxGeometry height="33" width="140" y="173.14285714285714" as="geometry" />
        </mxCell>
        <mxCell id="CtJBt8VR4UTQdoXEWvWE-34" parent="CtJBt8VR4UTQdoXEWvWE-27" style="text;strokeColor=none;fillColor=none;align=left;verticalAlign=top;spacingLeft=4;spacingRight=4;overflow=hidden;rotatable=0;points=[[0,0.5],[1,0.5]];portConstraint=eastwest;" value="+clear()" vertex="1">
          <mxGeometry height="33" width="140" y="206.14285714285714" as="geometry" />
        </mxCell>
        <mxCell id="CtJBt8VR4UTQdoXEWvWE-35" parent="1" style="swimlane;fontStyle=1;align=center;verticalAlign=top;childLayout=stackLayout;horizontal=1;startSize=34.666666666666664;horizontalStack=0;resizeParent=1;resizeParentMax=0;resizeLast=0;collapsible=0;marginBottom=0;fillColor=light-dark(#eeeeee,#1f2020);strokeColor=light-dark(#999999,#cccccc);fontColor=light-dark(#333333,#cccccc);" value="Player" vertex="1">
          <mxGeometry height="217.66666666666666" width="155" x="373" y="862" as="geometry" />
        </mxCell>
        <mxCell id="CtJBt8VR4UTQdoXEWvWE-36" parent="CtJBt8VR4UTQdoXEWvWE-35" style="text;strokeColor=none;fillColor=none;align=left;verticalAlign=top;spacingLeft=4;spacingRight=4;overflow=hidden;rotatable=0;points=[[0,0.5],[1,0.5]];portConstraint=eastwest;" value="-string name" vertex="1">
          <mxGeometry height="35" width="155" y="34.666666666666664" as="geometry" />
        </mxCell>
        <mxCell id="CtJBt8VR4UTQdoXEWvWE-37" parent="CtJBt8VR4UTQdoXEWvWE-35" style="text;strokeColor=none;fillColor=none;align=left;verticalAlign=top;spacingLeft=4;spacingRight=4;overflow=hidden;rotatable=0;points=[[0,0.5],[1,0.5]];portConstraint=eastwest;" value="-int score" vertex="1">
          <mxGeometry height="35" width="155" y="69.66666666666666" as="geometry" />
        </mxCell>
        <mxCell id="CtJBt8VR4UTQdoXEWvWE-38" parent="CtJBt8VR4UTQdoXEWvWE-35" style="line;strokeWidth=1;fillColor=none;align=left;verticalAlign=middle;spacingTop=-1;spacingLeft=3;spacingRight=3;rotatable=0;labelPosition=right;points=[];portConstraint=eastwest;strokeColor=inherit;" vertex="1">
          <mxGeometry height="8" width="155" y="104.66666666666666" as="geometry" />
        </mxCell>
        <mxCell id="CtJBt8VR4UTQdoXEWvWE-39" parent="CtJBt8VR4UTQdoXEWvWE-35" style="text;strokeColor=none;fillColor=none;align=left;verticalAlign=top;spacingLeft=4;spacingRight=4;overflow=hidden;rotatable=0;points=[[0,0.5],[1,0.5]];portConstraint=eastwest;" value="+getName()" vertex="1">
          <mxGeometry height="35" width="155" y="112.66666666666666" as="geometry" />
        </mxCell>
        <mxCell id="CtJBt8VR4UTQdoXEWvWE-40" parent="CtJBt8VR4UTQdoXEWvWE-35" style="text;strokeColor=none;fillColor=none;align=left;verticalAlign=top;spacingLeft=4;spacingRight=4;overflow=hidden;rotatable=0;points=[[0,0.5],[1,0.5]];portConstraint=eastwest;" value="+getScore()" vertex="1">
          <mxGeometry height="35" width="155" y="147.66666666666666" as="geometry" />
        </mxCell>
        <mxCell id="CtJBt8VR4UTQdoXEWvWE-41" parent="CtJBt8VR4UTQdoXEWvWE-35" style="text;strokeColor=none;fillColor=none;align=left;verticalAlign=top;spacingLeft=4;spacingRight=4;overflow=hidden;rotatable=0;points=[[0,0.5],[1,0.5]];portConstraint=eastwest;" value="+addScore()" vertex="1">
          <mxGeometry height="35" width="155" y="182.66666666666666" as="geometry" />
        </mxCell>
        <mxCell id="CtJBt8VR4UTQdoXEWvWE-42" parent="1" style="swimlane;fontStyle=1;align=center;verticalAlign=top;childLayout=stackLayout;horizontal=1;startSize=33.45454545454545;horizontalStack=0;resizeParent=1;resizeParentMax=0;resizeLast=0;collapsible=0;marginBottom=0;fillColor=light-dark(#eeeeee,#1f2020);strokeColor=light-dark(#999999,#cccccc);fontColor=light-dark(#333333,#cccccc);" value="Move" vertex="1">
          <mxGeometry height="165.45454545454544" width="241" x="20" y="874" as="geometry" />
        </mxCell>
        <mxCell id="CtJBt8VR4UTQdoXEWvWE-43" parent="CtJBt8VR4UTQdoXEWvWE-42" style="text;strokeColor=none;fillColor=none;align=left;verticalAlign=top;spacingLeft=4;spacingRight=4;overflow=hidden;rotatable=0;points=[[0,0.5],[1,0.5]];portConstraint=eastwest;" value="+bool pass" vertex="1">
          <mxGeometry height="33" width="241" y="33.45454545454545" as="geometry" />
        </mxCell>
        <mxCell id="CtJBt8VR4UTQdoXEWvWE-44" parent="CtJBt8VR4UTQdoXEWvWE-42" style="text;strokeColor=none;fillColor=none;align=left;verticalAlign=top;spacingLeft=4;spacingRight=4;overflow=hidden;rotatable=0;points=[[0,0.5],[1,0.5]];portConstraint=eastwest;" value="+char addedLetter" vertex="1">
          <mxGeometry height="33" width="241" y="66.45454545454545" as="geometry" />
        </mxCell>
        <mxCell id="CtJBt8VR4UTQdoXEWvWE-45" parent="CtJBt8VR4UTQdoXEWvWE-42" style="text;strokeColor=none;fillColor=none;align=left;verticalAlign=top;spacingLeft=4;spacingRight=4;overflow=hidden;rotatable=0;points=[[0,0.5],[1,0.5]];portConstraint=eastwest;" value="+Position addedPosition" vertex="1">
          <mxGeometry height="33" width="241" y="99.45454545454545" as="geometry" />
        </mxCell>
        <mxCell id="CtJBt8VR4UTQdoXEWvWE-46" parent="CtJBt8VR4UTQdoXEWvWE-42" style="text;strokeColor=none;fillColor=none;align=left;verticalAlign=top;spacingLeft=4;spacingRight=4;overflow=hidden;rotatable=0;points=[[0,0.5],[1,0.5]];portConstraint=eastwest;" value="+string word" vertex="1">
          <mxGeometry height="33" width="241" y="132.45454545454544" as="geometry" />
        </mxCell>
        <mxCell id="CtJBt8VR4UTQdoXEWvWE-48" parent="1" style="swimlane;fontStyle=1;align=center;verticalAlign=top;childLayout=stackLayout;horizontal=1;startSize=36.8;horizontalStack=0;resizeParent=1;resizeParentMax=0;resizeLast=0;collapsible=0;marginBottom=0;fillColor=light-dark(#eeeeee,#1f2020);strokeColor=light-dark(#999999,#cccccc);fontColor=light-dark(#333333,#cccccc);" value="Position" vertex="1">
          <mxGeometry height="192.8" width="183" x="313" y="1224" as="geometry" />
        </mxCell>
        <mxCell id="CtJBt8VR4UTQdoXEWvWE-49" parent="CtJBt8VR4UTQdoXEWvWE-48" style="text;strokeColor=none;fillColor=none;align=left;verticalAlign=top;spacingLeft=4;spacingRight=4;overflow=hidden;rotatable=0;points=[[0,0.5],[1,0.5]];portConstraint=eastwest;" value="+int row" vertex="1">
          <mxGeometry height="37" width="183" y="36.8" as="geometry" />
        </mxCell>
        <mxCell id="CtJBt8VR4UTQdoXEWvWE-50" parent="CtJBt8VR4UTQdoXEWvWE-48" style="text;strokeColor=none;fillColor=none;align=left;verticalAlign=top;spacingLeft=4;spacingRight=4;overflow=hidden;rotatable=0;points=[[0,0.5],[1,0.5]];portConstraint=eastwest;" value="+int col" vertex="1">
          <mxGeometry height="37" width="183" y="73.8" as="geometry" />
        </mxCell>
        <mxCell id="CtJBt8VR4UTQdoXEWvWE-51" parent="CtJBt8VR4UTQdoXEWvWE-48" style="line;strokeWidth=1;fillColor=none;align=left;verticalAlign=middle;spacingTop=-1;spacingLeft=3;spacingRight=3;rotatable=0;labelPosition=right;points=[];portConstraint=eastwest;strokeColor=inherit;" vertex="1">
          <mxGeometry height="8" width="183" y="110.8" as="geometry" />
        </mxCell>
        <mxCell id="CtJBt8VR4UTQdoXEWvWE-52" parent="CtJBt8VR4UTQdoXEWvWE-48" style="text;strokeColor=none;fillColor=none;align=left;verticalAlign=top;spacingLeft=4;spacingRight=4;overflow=hidden;rotatable=0;points=[[0,0.5],[1,0.5]];portConstraint=eastwest;" value="+equals()" vertex="1">
          <mxGeometry height="37" width="183" y="118.8" as="geometry" />
        </mxCell>
        <mxCell id="CtJBt8VR4UTQdoXEWvWE-53" parent="CtJBt8VR4UTQdoXEWvWE-48" style="text;strokeColor=none;fillColor=none;align=left;verticalAlign=top;spacingLeft=4;spacingRight=4;overflow=hidden;rotatable=0;points=[[0,0.5],[1,0.5]];portConstraint=eastwest;" value="+isNeighbour()" vertex="1">
          <mxGeometry height="37" width="183" y="155.8" as="geometry" />
        </mxCell>
        <mxCell id="CtJBt8VR4UTQdoXEWvWE-54" parent="1" style="swimlane;fontStyle=1;align=center;verticalAlign=top;childLayout=stackLayout;horizontal=1;startSize=34.666666666666664;horizontalStack=0;resizeParent=1;resizeParentMax=0;resizeLast=0;collapsible=0;marginBottom=0;fillColor=light-dark(#eeeeee,#1f2020);strokeColor=light-dark(#999999,#cccccc);fontColor=light-dark(#333333,#cccccc);" value="Dictionary" vertex="1">
          <mxGeometry height="217.66666666666666" width="197" x="620" y="880" as="geometry" />
        </mxCell>
        <mxCell id="CtJBt8VR4UTQdoXEWvWE-55" parent="CtJBt8VR4UTQdoXEWvWE-54" style="text;strokeColor=none;fillColor=none;align=left;verticalAlign=top;spacingLeft=4;spacingRight=4;overflow=hidden;rotatable=0;points=[[0,0.5],[1,0.5]];portConstraint=eastwest;" value="-vector words" vertex="1">
          <mxGeometry height="35" width="197" y="34.666666666666664" as="geometry" />
        </mxCell>
        <mxCell id="CtJBt8VR4UTQdoXEWvWE-56" parent="CtJBt8VR4UTQdoXEWvWE-54" style="line;strokeWidth=1;fillColor=none;align=left;verticalAlign=middle;spacingTop=-1;spacingLeft=3;spacingRight=3;rotatable=0;labelPosition=right;points=[];portConstraint=eastwest;strokeColor=inherit;" vertex="1">
          <mxGeometry height="8" width="197" y="69.66666666666666" as="geometry" />
        </mxCell>
        <mxCell id="CtJBt8VR4UTQdoXEWvWE-57" parent="CtJBt8VR4UTQdoXEWvWE-54" style="text;strokeColor=none;fillColor=none;align=left;verticalAlign=top;spacingLeft=4;spacingRight=4;overflow=hidden;rotatable=0;points=[[0,0.5],[1,0.5]];portConstraint=eastwest;" value="+loadFromFile()" vertex="1">
          <mxGeometry height="35" width="197" y="77.66666666666666" as="geometry" />
        </mxCell>
        <mxCell id="CtJBt8VR4UTQdoXEWvWE-58" parent="CtJBt8VR4UTQdoXEWvWE-54" style="text;strokeColor=none;fillColor=none;align=left;verticalAlign=top;spacingLeft=4;spacingRight=4;overflow=hidden;rotatable=0;points=[[0,0.5],[1,0.5]];portConstraint=eastwest;" value="+contains()" vertex="1">
          <mxGeometry height="35" width="197" y="112.66666666666666" as="geometry" />
        </mxCell>
        <mxCell id="CtJBt8VR4UTQdoXEWvWE-59" parent="CtJBt8VR4UTQdoXEWvWE-54" style="text;strokeColor=none;fillColor=none;align=left;verticalAlign=top;spacingLeft=4;spacingRight=4;overflow=hidden;rotatable=0;points=[[0,0.5],[1,0.5]];portConstraint=eastwest;" value="+normalize()" vertex="1">
          <mxGeometry height="35" width="197" y="147.66666666666666" as="geometry" />
        </mxCell>
        <mxCell id="CtJBt8VR4UTQdoXEWvWE-60" parent="CtJBt8VR4UTQdoXEWvWE-54" style="text;strokeColor=none;fillColor=none;align=left;verticalAlign=top;spacingLeft=4;spacingRight=4;overflow=hidden;rotatable=0;points=[[0,0.5],[1,0.5]];portConstraint=eastwest;" value="+getWords()" vertex="1">
          <mxGeometry height="35" width="197" y="182.66666666666666" as="geometry" />
        </mxCell>
        <mxCell id="CtJBt8VR4UTQdoXEWvWE-61" parent="1" style="swimlane;fontStyle=1;align=center;verticalAlign=top;childLayout=stackLayout;horizontal=1;startSize=47.2;horizontalStack=0;resizeParent=1;resizeParentMax=0;resizeLast=0;collapsible=0;marginBottom=0;fillColor=light-dark(#eeeeee,#1f2020);strokeColor=light-dark(#999999,#cccccc);fontColor=light-dark(#333333,#cccccc);" value="WordValidator" vertex="1">
          <mxGeometry height="94.2" width="222" x="999" y="602" as="geometry" />
        </mxCell>
        <mxCell id="CtJBt8VR4UTQdoXEWvWE-63" parent="CtJBt8VR4UTQdoXEWvWE-61" style="text;strokeColor=none;fillColor=none;align=left;verticalAlign=top;spacingLeft=4;spacingRight=4;overflow=hidden;rotatable=0;points=[[0,0.5],[1,0.5]];portConstraint=eastwest;" value="+validateMove()" vertex="1">
          <mxGeometry height="47" width="222" y="47.2" as="geometry" />
        </mxCell>
        <mxCell id="CtJBt8VR4UTQdoXEWvWE-64" parent="1" style="swimlane;fontStyle=1;align=center;verticalAlign=top;childLayout=stackLayout;horizontal=1;startSize=34.666666666666664;horizontalStack=0;resizeParent=1;resizeParentMax=0;resizeLast=0;collapsible=0;marginBottom=0;fillColor=light-dark(#eeeeee,#1f2020);strokeColor=light-dark(#999999,#cccccc);fontColor=light-dark(#333333,#cccccc);" value="BoardGraph" vertex="1">
          <mxGeometry height="217.66666666666666" width="246" x="940" y="884.33" as="geometry" />
        </mxCell>
        <mxCell id="CtJBt8VR4UTQdoXEWvWE-65" parent="CtJBt8VR4UTQdoXEWvWE-64" style="text;strokeColor=none;fillColor=none;align=left;verticalAlign=top;spacingLeft=4;spacingRight=4;overflow=hidden;rotatable=0;points=[[0,0.5],[1,0.5]];portConstraint=eastwest;" value="-vector&amp;gt; adjacency" vertex="1">
          <mxGeometry height="35" width="246" y="34.666666666666664" as="geometry" />
        </mxCell>
        <mxCell id="CtJBt8VR4UTQdoXEWvWE-66" parent="CtJBt8VR4UTQdoXEWvWE-64" style="line;strokeWidth=1;fillColor=none;align=left;verticalAlign=middle;spacingTop=-1;spacingLeft=3;spacingRight=3;rotatable=0;labelPosition=right;points=[];portConstraint=eastwest;strokeColor=inherit;" vertex="1">
          <mxGeometry height="8" width="246" y="69.66666666666666" as="geometry" />
        </mxCell>
        <mxCell id="CtJBt8VR4UTQdoXEWvWE-67" parent="CtJBt8VR4UTQdoXEWvWE-64" style="text;strokeColor=none;fillColor=none;align=left;verticalAlign=top;spacingLeft=4;spacingRight=4;overflow=hidden;rotatable=0;points=[[0,0.5],[1,0.5]];portConstraint=eastwest;" value="+build()" vertex="1">
          <mxGeometry height="35" width="246" y="77.66666666666666" as="geometry" />
        </mxCell>
        <mxCell id="CtJBt8VR4UTQdoXEWvWE-68" parent="CtJBt8VR4UTQdoXEWvWE-64" style="text;strokeColor=none;fillColor=none;align=left;verticalAlign=top;spacingLeft=4;spacingRight=4;overflow=hidden;rotatable=0;points=[[0,0.5],[1,0.5]];portConstraint=eastwest;" value="+getNeighbours()" vertex="1">
          <mxGeometry height="35" width="246" y="112.66666666666666" as="geometry" />
        </mxCell>
        <mxCell id="CtJBt8VR4UTQdoXEWvWE-69" parent="CtJBt8VR4UTQdoXEWvWE-64" style="text;strokeColor=none;fillColor=none;align=left;verticalAlign=top;spacingLeft=4;spacingRight=4;overflow=hidden;rotatable=0;points=[[0,0.5],[1,0.5]];portConstraint=eastwest;" value="+getPosition()" vertex="1">
          <mxGeometry height="35" width="246" y="147.66666666666666" as="geometry" />
        </mxCell>
        <mxCell id="CtJBt8VR4UTQdoXEWvWE-70" parent="CtJBt8VR4UTQdoXEWvWE-64" style="text;strokeColor=none;fillColor=none;align=left;verticalAlign=top;spacingLeft=4;spacingRight=4;overflow=hidden;rotatable=0;points=[[0,0.5],[1,0.5]];portConstraint=eastwest;" value="+getVertexNumber()" vertex="1">
          <mxGeometry height="35" width="246" y="182.66666666666666" as="geometry" />
        </mxCell>
        <mxCell id="CtJBt8VR4UTQdoXEWvWE-71" parent="1" style="swimlane;fontStyle=1;align=center;verticalAlign=top;childLayout=stackLayout;horizontal=1;startSize=34.54545454545455;horizontalStack=0;resizeParent=1;resizeParentMax=0;resizeLast=0;collapsible=0;marginBottom=0;fillColor=light-dark(#eeeeee,#1f2020);strokeColor=light-dark(#999999,#cccccc);fontColor=light-dark(#333333,#cccccc);" value="Logger" vertex="1">
          <mxGeometry height="174.54545454545456" width="149" x="150" y="566" as="geometry" />
        </mxCell>
        <mxCell id="CtJBt8VR4UTQdoXEWvWE-73" parent="CtJBt8VR4UTQdoXEWvWE-71" style="text;strokeColor=none;fillColor=none;align=left;verticalAlign=top;spacingLeft=4;spacingRight=4;overflow=hidden;rotatable=0;points=[[0,0.5],[1,0.5]];portConstraint=eastwest;" value="+open()" vertex="1">
          <mxGeometry height="35" width="149" y="34.54545454545455" as="geometry" />
        </mxCell>
        <mxCell id="CtJBt8VR4UTQdoXEWvWE-74" parent="CtJBt8VR4UTQdoXEWvWE-71" style="text;strokeColor=none;fillColor=none;align=left;verticalAlign=top;spacingLeft=4;spacingRight=4;overflow=hidden;rotatable=0;points=[[0,0.5],[1,0.5]];portConstraint=eastwest;" value="+logStart()" vertex="1">
          <mxGeometry height="35" width="149" y="69.54545454545455" as="geometry" />
        </mxCell>
        <mxCell id="CtJBt8VR4UTQdoXEWvWE-75" parent="CtJBt8VR4UTQdoXEWvWE-71" style="text;strokeColor=none;fillColor=none;align=left;verticalAlign=top;spacingLeft=4;spacingRight=4;overflow=hidden;rotatable=0;points=[[0,0.5],[1,0.5]];portConstraint=eastwest;" value="+logMove()" vertex="1">
          <mxGeometry height="35" width="149" y="104.54545454545455" as="geometry" />
        </mxCell>
        <mxCell id="CtJBt8VR4UTQdoXEWvWE-76" parent="CtJBt8VR4UTQdoXEWvWE-71" style="text;strokeColor=none;fillColor=none;align=left;verticalAlign=top;spacingLeft=4;spacingRight=4;overflow=hidden;rotatable=0;points=[[0,0.5],[1,0.5]];portConstraint=eastwest;" value="+logEnd()" vertex="1">
          <mxGeometry height="35" width="149" y="139.54545454545456" as="geometry" />
        </mxCell>
        <mxCell id="CtJBt8VR4UTQdoXEWvWE-77" edge="1" parent="1" source="CtJBt8VR4UTQdoXEWvWE-2" style="curved=1;startArrow=none;endArrow=open;endSize=12;exitX=1;exitY=0.6;entryX=0.858;entryY=0.007;rounded=0;entryDx=0;entryDy=0;entryPerimeter=0;" target="CtJBt8VR4UTQdoXEWvWE-18" value="использует">
          <mxGeometry relative="1" x="-0.0401" y="-31" as="geometry">
            <mxPoint as="offset" />
            <Array as="points">
              <mxPoint x="1150" y="470" />
              <mxPoint x="1410" y="740" />
            </Array>
          </mxGeometry>
        </mxCell>
        <mxCell id="CtJBt8VR4UTQdoXEWvWE-78" edge="1" parent="1" source="CtJBt8VR4UTQdoXEWvWE-2" style="curved=1;startArrow=none;endArrow=open;endSize=12;exitX=0;exitY=0.82;rounded=0;entryX=0.5;entryY=0;entryDx=0;entryDy=0;" target="CtJBt8VR4UTQdoXEWvWE-35" value="хранит игроков">
          <mxGeometry relative="1" as="geometry">
            <Array as="points">
              <mxPoint x="460" y="590" />
            </Array>
            <mxPoint x="499" y="850" as="targetPoint" />
          </mxGeometry>
        </mxCell>
        <mxCell id="CtJBt8VR4UTQdoXEWvWE-79" edge="1" parent="1" source="CtJBt8VR4UTQdoXEWvWE-2" style="curved=1;startArrow=none;endArrow=open;endSize=12;exitX=1;exitY=0.76;entryX=0.15;entryY=0;rounded=0;" target="CtJBt8VR4UTQdoXEWvWE-54" value="проверяет слова">
          <mxGeometry relative="1" as="geometry">
            <Array as="points">
              <mxPoint x="840" y="560" />
              <mxPoint x="650" y="750" />
            </Array>
          </mxGeometry>
        </mxCell>
        <mxCell id="CtJBt8VR4UTQdoXEWvWE-80" edge="1" parent="1" source="CtJBt8VR4UTQdoXEWvWE-2" style="curved=1;startArrow=none;endArrow=open;endSize=12;exitX=1;exitY=0.65;entryX=0.5;entryY=0;rounded=0;" target="CtJBt8VR4UTQdoXEWvWE-61" value="проверяет ход">
          <mxGeometry relative="1" as="geometry">
            <Array as="points">
              <mxPoint x="1110" y="529" />
            </Array>
          </mxGeometry>
        </mxCell>
        <mxCell id="CtJBt8VR4UTQdoXEWvWE-81" edge="1" parent="1" source="CtJBt8VR4UTQdoXEWvWE-2" style="curved=1;startArrow=none;endArrow=open;endSize=12;exitX=0;exitY=0.68;entryX=0.5;entryY=0;rounded=0;" target="CtJBt8VR4UTQdoXEWvWE-71" value="пишет лог">
          <mxGeometry relative="1" as="geometry">
            <Array as="points">
              <mxPoint x="224" y="529" />
            </Array>
          </mxGeometry>
        </mxCell>
        <mxCell id="CtJBt8VR4UTQdoXEWvWE-82" edge="1" parent="1" source="CtJBt8VR4UTQdoXEWvWE-2" style="curved=1;startArrow=none;endArrow=open;endSize=12;exitX=0;exitY=0.63;entryX=0.31;entryY=0;rounded=0;" target="CtJBt8VR4UTQdoXEWvWE-42" value="получает ход">
          <mxGeometry relative="1" x="0.0096" y="40" as="geometry">
            <mxPoint as="offset" />
            <Array as="points">
              <mxPoint x="58" y="529" />
              <mxPoint x="58" y="801" />
            </Array>
          </mxGeometry>
        </mxCell>
        <mxCell id="CtJBt8VR4UTQdoXEWvWE-83" edge="1" parent="1" source="CtJBt8VR4UTQdoXEWvWE-18" style="curved=1;startArrow=none;endArrow=open;endSize=12;exitX=0.5;exitY=1;entryX=0.5;entryY=0;rounded=0;" target="CtJBt8VR4UTQdoXEWvWE-27" value="состоит из клеток">
          <mxGeometry relative="1" as="geometry">
            <Array as="points" />
          </mxGeometry>
        </mxCell>
        <mxCell id="CtJBt8VR4UTQdoXEWvWE-84" edge="1" parent="1" source="CtJBt8VR4UTQdoXEWvWE-42" style="curved=1;startArrow=none;endArrow=open;endSize=12;exitX=0.5;exitY=1;entryX=0;entryY=0.19;rounded=0;" target="CtJBt8VR4UTQdoXEWvWE-48" value="содержит координаты">
          <mxGeometry relative="1" as="geometry">
            <Array as="points">
              <mxPoint x="141" y="1151" />
            </Array>
          </mxGeometry>
        </mxCell>
        <mxCell id="CtJBt8VR4UTQdoXEWvWE-85" edge="1" parent="1" source="CtJBt8VR4UTQdoXEWvWE-61" style="curved=1;startArrow=none;endArrow=open;endSize=12;exitX=1;exitY=0.95;entryX=0.18;entryY=-0.007;rounded=0;entryDx=0;entryDy=0;entryPerimeter=0;" target="CtJBt8VR4UTQdoXEWvWE-18" value="читает поле">
          <mxGeometry relative="1" as="geometry">
            <Array as="points" />
          </mxGeometry>
        </mxCell>
        <mxCell id="CtJBt8VR4UTQdoXEWvWE-86" edge="1" parent="1" source="CtJBt8VR4UTQdoXEWvWE-61" style="curved=1;startArrow=none;endArrow=open;endSize=12;exitX=0.5;exitY=1;entryX=0.85;entryY=0;rounded=0;" target="CtJBt8VR4UTQdoXEWvWE-54" value="проверяет словарь">
          <mxGeometry relative="1" as="geometry">
            <Array as="points">
              <mxPoint x="1030" y="760" />
            </Array>
          </mxGeometry>
        </mxCell>
        <mxCell id="CtJBt8VR4UTQdoXEWvWE-87" edge="1" parent="1" source="CtJBt8VR4UTQdoXEWvWE-63" style="curved=1;startArrow=none;endArrow=open;endSize=12;entryX=0.5;entryY=0;rounded=0;" target="CtJBt8VR4UTQdoXEWvWE-64" value="ищет путь слова">
          <mxGeometry relative="1" as="geometry">
            <Array as="points">
              <mxPoint x="1130" y="780" />
            </Array>
          </mxGeometry>
        </mxCell>
        <mxCell id="CtJBt8VR4UTQdoXEWvWE-88" edge="1" parent="1" source="CtJBt8VR4UTQdoXEWvWE-64" style="curved=1;startArrow=none;endArrow=open;endSize=12;exitX=0.5;exitY=1;entryX=1;entryY=0.24;rounded=0;" target="CtJBt8VR4UTQdoXEWvWE-48" value="работает с координатами">
          <mxGeometry relative="1" x="-0.0424" y="-37" as="geometry">
            <mxPoint x="1" as="offset" />
            <Array as="points">
              <mxPoint x="800" y="1260" />
            </Array>
          </mxGeometry>
        </mxCell>
        <mxCell id="CtJBt8VR4UTQdoXEWvWE-89" edge="1" parent="1" source="CtJBt8VR4UTQdoXEWvWE-71" style="curved=1;startArrow=none;endArrow=open;endSize=12;exitX=1;exitY=0.68;entryX=0.25;entryY=0;rounded=0;entryDx=0;entryDy=0;" target="CtJBt8VR4UTQdoXEWvWE-35" value="записывает игрока">
          <mxGeometry relative="1" as="geometry">
            <Array as="points">
              <mxPoint x="390" y="810" />
            </Array>
          </mxGeometry>
        </mxCell>
        <mxCell id="CtJBt8VR4UTQdoXEWvWE-90" edge="1" parent="1" source="CtJBt8VR4UTQdoXEWvWE-71" style="curved=1;startArrow=none;endArrow=open;endSize=12;exitX=0.5;exitY=1;entryX=0.7;entryY=0;rounded=0;" target="CtJBt8VR4UTQdoXEWvWE-42" value="записывает ход">
          <mxGeometry relative="1" as="geometry">
            <Array as="points">
              <mxPoint x="224" y="801" />
            </Array>
          </mxGeometry>
        </mxCell>
      </root>
    </mxGraphModel>
  </diagram>
</mxfile>
```
