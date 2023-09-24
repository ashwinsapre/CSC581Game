class Rectangle : public sf::RectangleShape{
public:
    Rectangle(){}

    void init(float sizeX, float sizeY, float initX, float initY){
        setSize(sf::Vector2f(sizeX, sizeY));
        setPosition(sf::Vector2f(initX, initY));
    }

    sf::FloatRect getBoundingBox(){
        return getGlobalBounds();
    }
};