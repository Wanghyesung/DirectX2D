#pragma once

#include "WResource.h"

namespace W
{
	class Resources
	{
	public:
		template <typename T>
		static T* Find(const std::wstring& _strKey)
		{
			//���ҽ��ʿ��� �����͸� Ž���Ѵ� �����Ͱ� �ִٸ� �ش絥���͸� ��ȯ�ϰ�
			//�����Ͱ� ���ٸ� end�� ��ȯ���ش�.
			std::map<std::wstring, Resource*>::iterator iter = m_mapResources.find(_strKey);

			//ã���� �ϴ� �����Ͱ� �����Ѵٸ�
			//�ش�Ÿ������ ����ȯ�Ͽ� ��ȯ
			if (iter != m_mapResources.end())
			{
				return dynamic_cast<T*>(iter->second);
			}

			//������ ���ٸ� ���� ��ȯ
			return nullptr;
		}

		template <typename T>
		static T* Load(const std::wstring& _strKey, const std::wstring& _strPath)
		{
			// Ű������ Ž��
			T* resource = Resources::Find<T>(_strKey);
			if (resource != nullptr)
			{
				return resource;
			}

			// �ش� ���ҽ��� ���ٸ�
			resource = new T();
			if (FAILED(resource->Load(_strPath)))
			{
				assert(false);
				return nullptr;
			}

			resource->SetKey(_strKey);
			resource->SetPath(_strPath);
			m_mapResources.insert(std::make_pair(_strKey, resource));

			return dynamic_cast<T*>(resource);
		}

		template <typename T>
		static void Insert(const std::wstring& _strKey, T* _pResource)
		{
			m_mapResources.insert(std::make_pair(_strKey, _pResource));
		}

		static void Release()
		{
			for (auto pair : m_mapResources)
			{
				delete pair.second;
				pair.second = nullptr;
			}
		}

	private:
		static std::map<std::wstring, Resource*> m_mapResources;
	};
}

