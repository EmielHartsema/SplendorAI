#pragma once

#include <vector>
#include <optional>
#include <cstdlib>

enum class Juwel
{
    Red,
    Green,
    Blue,
    Black,
    White,
    Pearl,
    Gold
};

class JuwelCollection
{
public:
    JuwelCollection();

    JuwelCollection( int nr_red,
                     int nr_green,
                     int nr_blue,
                     int nr_black,
                     int nr_white,
                     int nr_pearl,
                     int nr_gold);

    JuwelCollection(const std::vector<Juwel>& juwels);

    int amount() const;
    int amount(Juwel juwel) const;
    bool empty() const;

    void add(Juwel juwel);
    bool remove(Juwel juwel);

    std::optional<Juwel> take_random();

private:

    int m_nr_red;
    int m_nr_green;
    int m_nr_blue;
    int m_nr_black;
    int m_nr_white;
    int m_nr_pearl;
    int m_nr_gold;
};
