#include <iostream>
#include <cctype>
#include <new>

namespace oztas
{
    size_t rpl_sym(const char* src, char* dst, size_t dst_size, char from, char to)
    {
        size_t i = 0;

        while (src[i] != '\0' && i + 1 < dst_size)
        {
            dst[i] = (src[i] == from) ? to : src[i];
            ++i;
        }

        dst[i] = '\0';
        return i;
    }

    size_t lat_two(const char* s1, const char* s2, char* dst, size_t dst_size)
    {
        int used[26] = { 0 };
        size_t count = 0;

        for (size_t i = 0; s1[i] != '\0'; ++i)
        {
            unsigned char c = static_cast<unsigned char>(s1[i]);
            if (std::isalpha(c))
                used[std::tolower(c) - 'a'] = 1;
        }

        for (size_t i = 0; s2[i] != '\0'; ++i)
        {
            unsigned char c = static_cast<unsigned char>(s2[i]);
            if (std::isalpha(c))
                used[std::tolower(c) - 'a'] = 1;
        }

        for (int i = 0; i < 26 && count + 1 < dst_size; ++i)
        {
            if (used[i])
                dst[count++] = static_cast<char>('a' + i);
        }

        dst[count] = '\0';
        return count;
    }
}

char* read_line()
{
    size_t capacity = 16;
    size_t length = 0;
    char* buffer = nullptr;

    try
    {
        buffer = new char[capacity];
    }
    catch (const std::bad_alloc&)
    {
        return nullptr;
    }

    int ch;
    while ((ch = std::cin.get()) != '\n' && ch != EOF)
    {
        if (length + 1 >= capacity)
        {
            size_t new_capacity = capacity * 2;
            char* temp = nullptr;

            try
            {
                temp = new char[new_capacity];
            }
            catch (const std::bad_alloc&)
            {
                delete[] buffer;
                return nullptr;
            }

            for (size_t i = 0; i < length; ++i)
                temp[i] = buffer[i];

            delete[] buffer;
            buffer = temp;
            capacity = new_capacity;
        }

        buffer[length++] = static_cast<char>(ch);
    }

    buffer[length] = '\0';
    return buffer;
}

int main()
{
    char* input = read_line();
    if (!input)
    {
        std::cerr << "Memory allocation error\n";
        return 1;
    }

    size_t len = 0;
    while (input[len] != '\0')
        ++len;

    char* result1 = nullptr;
    char* result2 = nullptr;

    try
    {
        result1 = new char[len + 1];
        result2 = new char[27];
    }
    catch (const std::bad_alloc&)
    {
        delete[] input;
        std::cerr << "Memory allocation error\n";
        return 1;
    }

    oztas::rpl_sym(input, result1, len + 1, 'c', 'b');
    std::cout << result1 << '\n';

    const char second[] = "def_ghk";
    oztas::lat_two(input, second, result2, 27);
    std::cout << result2 << '\n';

    delete[] input;
    delete[] result1;
    delete[] result2;

    return 0;
}
