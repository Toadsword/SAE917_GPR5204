/*
MIT License

Copyright (c) 2017 SAE Institute Switzerland AG

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#include <map>
#include <vector>
#include <string>
#include <memory>

#include <benchmark/benchmark.h>

using ElementData = std::array<char,4>;
struct Element
{
    ElementData data;
};

const size_t ElemNmb = 10'000;

static std::string RandomString(int maxSize)
{
    unsigned randomSize = rand()%maxSize;
    char newKey[randomSize];
    for(auto i = 0u; i<randomSize;i++)
    {
        if(i < randomSize-1)
            newKey[i] = rand()%256;
        else
            newKey[i] = 0;

    }
    return std::string(newKey);
}

class MapSystem
{
private:
    std::map<std::string, Element> m_MapElements;
public:
    void AddElement(std::string key, ElementData& data)
    {
        Element elem;
        elem.data = data;
        m_MapElements[key] = elem;
    }
    void FindElement(std::string key)
    {

    }
    void Update(ElementData& newElem)
    {
        for(auto& pair: m_MapElements)
        {
            pair.second.data = newElem;
        }
    }

    void Prefill(size_t size)
    {
        ElementData data;
        *data.data() = *"GAM";

        for(auto i = 0u; i<size;i++)
        {
            AddElement(RandomString(20), data);
        }
    }
};

class VectorSystem
{
private:
    std::vector<std::string> m_Keys;
    std::vector<Element> m_Values;
    int incrementalValue = 0;
public:
    void AddElement(std::string key, ElementData& data)
    {
        m_Keys[incrementalValue] = key;
        m_Values[incrementalValue].data = data;
        incrementalValue++;
        if(incrementalValue >= m_Keys.size())
        {
            incrementalValue = 0;
        }
    }
    void FindElement(std::string key)
    {

    }
    void Update(ElementData& newElem)
    {
        for(auto& value: m_Values)
        {
            value.data = newElem;
        }
    }
    void Prefill(size_t size)
    {
        ElementData data;
        *data.data() = *"GAM";

        m_Keys.resize(size);
        m_Values.resize(size);
        for(auto i = 0u; i<size;i++)
        {
            std::string randomString = RandomString(20);
            AddElement(randomString, data);
        }
    }
};


static void BM_MapUpdate(benchmark::State& state)
{
    auto mapSystem = std::make_unique<MapSystem>();
    mapSystem->Prefill(ElemNmb);
    ElementData data;

    *data.data() = *"GPR";
    for (auto _ : state)
    {
        mapSystem->Update(data);
    }
}
//BENCHMARK(BM_MapUpdate);


static void BM_VectorUpdate(benchmark::State& state) {
    auto vectorSystem = std::make_unique<VectorSystem>();
    vectorSystem->Prefill(ElemNmb);
    ElementData data;
    *data.data() = *"GPR";
    for (auto _ : state)
    {
        vectorSystem->Update(data);
    }
}
BENCHMARK(BM_VectorUpdate);

BENCHMARK_MAIN();
