#include "Transform.h"

bool boogleborg::Transform::Write(const rapidjson::Value& value) const
{
    return true;
}

bool boogleborg::Transform::Read(const rapidjson::Value& value)
{
    READ_DATA(value, position);
    READ_DATA(value, scale);

    glm::vec3 euler{ 0 };
    READ_NAME_DATA(value, "rotation", euler);
    rotation = math::EulerToQuaternion(euler);

    return true;
}
