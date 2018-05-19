# Find-job
# Описание игры
Find-job - игра, в которой стажер стремится попасть на собеседование. Создается офис, который формально означает лабиринт. Офис разбит на ячейки (рабочие места: Workplace), в каждой ячейке сидит сотрудник (Worker). Он может быть злым, добрым и т.д. Также после посещения клетки происходят определенные действия (Actions), которые указывают на дальнейшую судьбу стажера. Таким образом, в зависимости от сутрудника и его настроения со стажером может происходить много событий: он может быть выкинут из офиса, может получить в подарок куклу, чтобы отбиваться от злых сотрудников, и т.д. В зависимости от структуры лабиринта игрок будет каждый ход получать от математической модели (которая пока что не сделана) необходимые и достаточные подсказки, чтобы не попасть к злому сотруднику (например: 'в радиусе 2 ячеек находятся 5 злых сотрудников','слева от вас точно злой сотрудник')

# Архитектура
Все сотрудники и действия после заходов в офисную ячейку создаются с помощью фабрик Worker и Actions. У нас есть несколько классов, которые являются однотипными, но каждый имеет собственные реализации, что говорит о разумности применения паттерна проектирования AbstractFabric. Делаем конкретные фабрики (Good/Bad/VeryGood/Tea/Win)Workplace, которые наследуются от абстрактной фабрики WorkplaceFactory. Также у нас есть FractionMarketing, состоящая из некоторых элементов BadWorkplace, с которыми надо иметь возможность выполнять общие действие, для чего и необходим паттерн Composite. Эти конкретные фабрики создают нам рабочие места - "офисные ячейки", которые в виде карты хранятся в отдельном классе - Office. Чтобы при попадании к плохому работнику, у игрока был шанс не вылететь, мы "перехватываем" строгие действия вылетания с помощью ChanceStep, реализуя это с помощью паттерна Proxy, так как именно он помогает предоставить объект, который контролирует доступ к другому объекту. Сама же карта офиса и все ячейки в нем создаются в классе Game. В этом же классе происходит и сам процесс игры - продвижение игрока по офисному лабиринту. Для вывода подсказок того, что находится на пути игрока используем паттерн Decorator, что отлично подходит в данном случае, ибо он как раз навешивает дополнительную информацию к уже имеющейся. У нас есть DecoratorW, который с помощью своих наследников DecoratorHelp и DecoratorInfo дает нужную информацию игроку.
Для реализации хождения по лабиринту офиса используем поведенческий паттерн Command. Есть класс Receiver, который получает команды (для команд есть класс Command и его наследник - UsualCommand). Информацию о необходимых действиях Recevier получает в классе Game во время процесса игры. Плюс ко всему Recevier хранит выполняемые команды, что может дать возможность посмотреть полный путь прохождения лабиринта и всех действий игрока. Паттерн Visitor  реализован с помощью одноименного класса и его наследника - ShowArea. В определенный момент он посещает все ячейки вокруг точки нахождения игрока и выводит информацию о них в качестве подсказки, что очень удобно. Для уведомления об изменении статуса злых работников внутри лабиринта (после нахождения эликсира) используется паттерн *Observer*: есть класс Notifications, хранящий список игркоков, которым нужно присылать уведомления (в нашем случае игрок всего один).

В игре представлен пример игры в офисе размером 28х10 (не включаются граничные сотрудники).
Схема архитектуры объемная, поэтому для удобства поведенческие паттерны вынесены в отдельные схемы.
