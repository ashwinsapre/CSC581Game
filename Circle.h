class Circle : public sf::CircleShape{
public:
    float xvel = 0;
    float yvel = 0;

    Circle(){}

    void init(float size, float initX, float initY){
        setRadius(size);
        setPosition(sf::Vector2f(initX, initY));
    }

    sf::FloatRect getBoundingBox(){
        return getGlobalBounds();
    }
};