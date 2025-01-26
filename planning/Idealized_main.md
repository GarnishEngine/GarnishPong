#### An idealized version of the main file assuming GarnishEngine is done

```cpp
int main() {
    garnish::GarnishApp app{};
    try {
        app.run();
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
```