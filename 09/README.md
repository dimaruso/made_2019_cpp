### Домашнее задание

### Пул потоков (thread pool)

Создание потока - дорогая операция, поэтому иногда хочется этого избежать.

Идея:

1. Создаем N потоков, каждый поток либо выполняет задачу, либо спит
2. Новая задача добавляется в очередь, при этом происходит оповещение спящих потоков
3. Проснувшись поток проверяет, что в очереди есть задача, после чего извлекает ее из очереди и выполняет
4. Если задачи нет, поток засыпает ожидая оповещения

Реализовать пул потоков со следующим интерфейсом:

```c++
class ThreadPool
{
public:
    explicit ThreadPool(size_t poolSize);

     // pass arguments by value
    template <class Func, class... Args>
    auto exec(Func func, Args... args) -> std::future<decltype(func(args...))>;
};
```

Использование пула потоков:

```c++
struct A {};

void foo(const A&) {}

ThreadPool pool(8);

auto task1 = pool.exec(foo, A());
task1.get();

auto task2 = pool.exec([]() { return 1; });
task2.get();
```
