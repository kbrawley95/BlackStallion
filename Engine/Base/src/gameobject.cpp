GameObject::GameObject(std::string givenName)
{
    name = givenName;
    transform = new Transform();
    attached_components.clear();
}

GameObject::~GameObject()
{
    for (int i = 0; i < attached_components.size(); i++)
    {
        delete attached_components[i];
    }
    attached_components.clear();
}

std::string GameObject::getName()
{
    return name;
}

void GameObject::setName(std::string value)
{
    name = value;
}

Transform* GameObject::getTransform()
{
    return transform;
}

void GameObject::addComponent(Component* component)
{
    component->gameObject = this;
    attached_components.push_back(component);
}

std::vector<Component*> GameObject::getAttachedComponents()
{
    return attached_components;
}
