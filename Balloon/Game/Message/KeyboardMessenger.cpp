#include "pch.h"
#include "Game/Message/KeyboardMessenger.h"
#include "Framework/InputManager.h"


KeyboardMessenger::KeyboardMessenger()
{
    m_inputManager = InputManager::GetInstance();
}

void KeyboardMessenger::Attach(const KeyType& type, const DirectX::Keyboard::Keys& keys, IObject* observer)
{
	// “o˜^‚·‚é
	m_observerList[type].emplace(keys, observer);
}



void KeyboardMessenger::Dispatch()
{
    for (const auto& [keyType, multimap] : m_observerList)
    {
        for (const auto& [key, observer] : multimap)
        {
            bool isActive = false;

            switch (keyType)
            {
                case KeyType::ON_KEY:
                    isActive = m_inputManager->OnKey(key);
                    break;
                case KeyType::ON_KEY_DOWN:
                    isActive = m_inputManager->OnKeyDown(key);
                    break;
                case KeyType::ON_KEY_UP:
                    isActive = m_inputManager->OnKeyUp(key);
                    break;
            }

            if (isActive)
            {
                observer->OnKeyPressed(keyType, key);
            }
        }
    }
}