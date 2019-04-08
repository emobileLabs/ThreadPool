# Concurrent / ThreadPool

ThreadPool Implementation using C++ 11, this pattern allows tasks/jobs asynchronously

## Design

- **TheadPool** class submit task queue (it takes any Callable Types), instantiates thread to run the task
- **TaskQueue** class contains queue of tasks to run
- **TaskThread** class to read the tasks and executes

## Usage

```
// Create thread pool with single thread
std::shared_ptr<ThreadPool> tp = std::make_shared<ThreadPool>(1);
// Function object or Callable Type
std::function<void()> func = []() { std::cout << "Inside function\n"; };
// Run the function object in a different thread
tp->submitTask(func);
```

## Build

Steps for compile the project

```
$ git clone <project.git>
$ mkdir build; cd build
$ cmake ..
$ make
```

## Run

```
$ cd build
build $ ./threadpool_app
```


### Reference

- https://en.wikipedia.org/wiki/Thread_pool