#pragma once

class IMaterial;
class IObject;

class Model3D
{
public:
	// ���f�����擾����
	DirectX::Model* GetModel() const { return m_model; }
	// �I�u�W�F�N�g���擾����
	IObject* GetObject() const { return m_object; }
	// �e��`�悷�邩
	bool GetIsShadow() const { return m_isShadow; }

public:
	// �R���X�g���N�^
	Model3D();
	// �f�X�g���N�^
	~Model3D() = default;

public:
	// ������
	void Initialize(DirectX::Model* model , IMaterial* material , IObject* object , bool isShadow = true);
	// �`�揈��
	void Render(ID3D11DeviceContext1* context , DirectX::CommonStates* states ,
		DirectX::SimpleMath::Matrix viewMatrix , DirectX::SimpleMath::Matrix projectionMatrix,
		ID3D11Buffer* lightBuffer
		);

private:
	// ���f��
	DirectX::Model* m_model;
	// �}�e���A��
	IMaterial* m_material;
	// �I�u�W�F�N�g
	IObject* m_object;

	// �e
	bool m_isShadow;
};