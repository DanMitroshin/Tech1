# Find-job
# Описание игры
Find-job - игра, в которой стажер стремится попасть на собеседование. Создается офис, который формально означает лабиринт. Офис разбит на ячейки (рабочие места: Workplace), в каждой ячейке сидит сотрудник (Worker). Он может быть злым, добрым и т.д. Также после посещения клетки происходят определенные действия (Actions), которые указывают на дальнейшую судьбу стажера. Таким образом, в зависимости от сутрудника и его настроения со стажером может происходить много событий: он может быть выкинут из офиса, может получить в подарок куклу, чтобы отбиваться от злых сотрудников, и т.д.

# Архитектура
Все сотрудники и действия после заходов в офисную ячейку создаются с помощью фабрик Worker и Actions. Различные комбинации вида (сотрудник + действие) комбинируются и создаются абстрактной фабрикой WorkplaceFactory. Очевидно, что здесь у нас есть взаимозависимости, которые обладают не очень простой логикой создания. К тому же здесь огромной пространство для воображения: в процессе реализации игры можно создавать больше видов сотрудников с нетривиальными свойствами, что показывает использование абстрактной фабрики очевидным плюсом в реализации. Все данные об офисе (его "карте") хранятся в классе Office. В игре представлен пример создания офиса размером 10х10.
