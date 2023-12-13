//1) реализовать блокировку низкоприоритетного запроса высокоприоритетным
// #include "mbed.h" 

// Thread High_priority(osPriorityHigh, OS_STACK_SIZE,nullptr,nullptr);
// Thread Low_priority(osPriorityLow, OS_STACK_SIZE,nullptr,nullptr);

// void highPriorityTask() //функция с высоким приоритетом
// {
    
//     printf("Выполняется высокоприоритетная задача\r\n");
//     printf("Высокоприоритетная задача выполнена\r\n");
    
// }
// void lowPriorityTask() //функция с низким приоритетом
// {
//     printf("Выполняется низкоприоритетная задача\r\n");
//     ThisThread::sleep_for(3s);  // Задержка для имитации выполнения длительной задачи
//     printf("Низкоприоритетная задача выполнена\r\n");

// }
// int main()
// {
//     Low_priority.start(callback(lowPriorityTask));
//     ThisThread::sleep_for(1s);
//     High_priority.start(callback(highPriorityTask));
// }

//2) реализовать блокировку потока через заблокированный другим потоком мьютекс
#include "mbed.h"

Thread t1(osPriorityNormal);
Thread t2(osPriorityHigh);
Mutex mutex1;

void notify1(){
    
        if (mutex1.trylock()){
            printf("Поток 1 ждет освобождения мьютекса\n");
            printf("Поток 1 получил мьютекс\n Hello from t1\n");      
            ThisThread::sleep_for(2s);  // Имитация выполнения работы
            mutex1.unlock(); // Поток отпускает мьютекс после выполнени действий
            ThisThread::sleep_for(1s);
        }
}
void notify2(){
    if (mutex1.trylock()){
    printf("Поток 2 начинает выполнение\n");
    printf("Hello from t2\n");
    ThisThread::sleep_for(1s);  // Имитация выполнения работы
    }
}
int main()
{ 
t1.start(notify1);
t2.start(notify2);
}


//3) продемонстрировать обмен данными между 2мя потоками через очередь
// #include "mbed.h" 
// typedef struct {
//  uint32_t counter;
// } message_t;

// MemoryPool<message_t, 16> pool;
// Queue<message_t, 16> queue;
// Thread thread;
// void send_thread(void)
// {
//  uint32_t i = 0;
// while(true)
// {
//     i++;
//     message_t *message = pool.alloc();
//     message->counter = i;
//     queue.put(message);
//     ThisThread::sleep_for(1s);
// } 
// }
// int main(void)
// {
//     thread.start(callback(send_thread));
//     while (true) 
//     {
//         osEvent evt = queue.get();
//         if (evt.status == osEventMessage) {
//         message_t *message = (message_t *)evt.value.p;
//         printf("Номер цикла: %u\n\r", message->counter);
//         pool.free(message);
//     }
//     }
// }
