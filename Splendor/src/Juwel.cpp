#include <Juwel.hpp>

JuwelCollection::JuwelCollection() : 
    m_nr_red(0),
    m_nr_green(0),
    m_nr_blue(0),
    m_nr_black(0),
    m_nr_white(0),
    m_nr_pearl(0),
    m_nr_gold(0)
{
};

JuwelCollection::JuwelCollection( int nr_red,
                                  int nr_green,
                                  int nr_blue,
                                  int nr_black,
                                  int nr_white,
                                  int nr_pearl,
                                  int nr_gold) :
    m_nr_red(nr_red),
    m_nr_green(nr_green),
    m_nr_blue(nr_blue),
    m_nr_black(nr_black),
    m_nr_white(nr_white),
    m_nr_pearl(nr_pearl),
    m_nr_gold(nr_gold)
{
};

JuwelCollection::JuwelCollection( const std::vector<Juwel>& juwels)
{
    m_nr_red   = 0;
    m_nr_green = 0;
    m_nr_blue  = 0;
    m_nr_black = 0;
    m_nr_white = 0;
    m_nr_pearl = 0;
    m_nr_gold  = 0;

    for (const Juwel& juwel : juwels)
    {
        switch (juwel)
        {
        case Juwel::Red:
            ++m_nr_red;
            break;
        case Juwel::Green:
            ++m_nr_green;
            break;
        case Juwel::Blue:
            ++m_nr_blue;
            break;
        case Juwel::Black:
            ++m_nr_black;
            break;
        case Juwel::White:
            ++m_nr_white;
            break;
        case Juwel::Pearl:
            ++m_nr_pearl;
            break;
        case Juwel::Gold:
            ++m_nr_gold;
            break;
        default:
            break;
        }
    }
}

std::optional<Juwel> JuwelCollection::take_random()
{
    const int total = amount();

    if (total == 0)
        return std::nullopt;

    int index = rand() % total;

    if (index < m_nr_red)
    {
        --m_nr_red;
        return Juwel::Red;
    }

    index -= m_nr_red;

    if (index < m_nr_green)
    {
        --m_nr_green;
        return Juwel::Green;
    }

    index -= m_nr_green;

    if (index < m_nr_blue)
    {
        --m_nr_blue;
        return Juwel::Blue;
    }

    index -= m_nr_blue;

    if (index < m_nr_black)
    {
        --m_nr_black;
        return Juwel::Black;
    }

    index -= m_nr_black;

    if (index < m_nr_white)
    {
        --m_nr_white;
        return Juwel::White;
    }

    index -= m_nr_white;

    if (index < m_nr_pearl)
    {
        --m_nr_pearl;
        return Juwel::Pearl;
    }

    --m_nr_gold;
    return Juwel::Gold;
}

int JuwelCollection::amount() const
{
    return m_nr_red   + 
            m_nr_green +
            m_nr_blue  +
            m_nr_black +
            m_nr_white +
            m_nr_pearl +
            m_nr_gold;
}

int JuwelCollection::amount(const Juwel juwel) const
{
    switch (juwel)
    {
    case Juwel::Red:
        return m_nr_red;
    case Juwel::Green:
        return m_nr_green;
    case Juwel::Blue:
        return m_nr_blue;
    case Juwel::Black:
        return m_nr_black;
    case Juwel::White:
        return m_nr_white;
    case Juwel::Pearl:
        return m_nr_pearl;
    case Juwel::Gold:
        return m_nr_gold;
    }
    return 0;
}

bool JuwelCollection::empty() const
{
    return amount() == 0;
}


void JuwelCollection::add(Juwel juwel)
{
    switch (juwel)
    {
    case Juwel::Red:
        m_nr_red++;
        break;
    case Juwel::Green:
        m_nr_green++;
        break;
    case Juwel::Blue:
        m_nr_blue++;
        break;
    case Juwel::Black:
        m_nr_black++;
        break;
    case Juwel::White:
        m_nr_white++;
        break;
    case Juwel::Pearl:
        m_nr_pearl++;
        break;
    case Juwel::Gold:
        m_nr_gold++;
        break;
    default:
        break;
    }
}

bool JuwelCollection::remove(Juwel juwel)
{
    switch (juwel)
    {
    case Juwel::Red:
        if (m_nr_red == 0) return false;
        --m_nr_red;
        return true;

    case Juwel::Green:
        if (m_nr_green == 0) return false;
        --m_nr_green;
        return true;

    case Juwel::Blue:
        if (m_nr_blue == 0) return false;
        --m_nr_blue;
        return true;

    case Juwel::Black:
        if (m_nr_black == 0) return false;
        --m_nr_black;
        return true;

    case Juwel::White:
        if (m_nr_white == 0) return false;
        --m_nr_white;
        return true;

    case Juwel::Pearl:
        if (m_nr_pearl == 0) return false;
        --m_nr_pearl;
        return true;

    case Juwel::Gold:
        if (m_nr_gold == 0) return false;
        --m_nr_gold;
        return true;
    }

    return false;
}