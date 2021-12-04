#ifndef _Point_H_
#define _Point_H_

template<typename TYPE>
class Point
{
public:
    Point(TYPE x, TYPE y);
    virtual ~Point(){};

    virtual TYPE getX(void);
    virtual TYPE getY(void);
    virtual void setX(TYPE x);
    virtual void setY(TYPE y);
private:
    TYPE m_x;
    TYPE m_y;
};

/**
* @brief constructor.
* @param[in] x initialize the member of x by that.
* @param[in] y initialize the member of y by that.
*/
template<typename TYPE>
Point<TYPE>::Point(TYPE x, TYPE y)
{
    this->m_x = x;
    this->m_y = y;
}

/**
* @brief Return x.
*
* @return TYPE x
*/
template<typename TYPE>
TYPE Point<TYPE>::getX(void)
{
    return this->m_x;
}

/**
* @brief Return y.
*
* @return TYPE y
*/
template<typename TYPE>
TYPE Point<TYPE>::getY(void)
{
    return this->m_y;
}

/**
* @brief Set x.
*/
template<typename TYPE>
void Point<TYPE>::setX(TYPE x)
{
    this->m_x = x;
}

/**
* @brief Set y.
*/
template<typename TYPE>
void Point<TYPE>::setY(TYPE y)
{
    this->m_y = y;
}

#endif // _Point_H_