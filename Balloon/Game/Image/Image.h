#pragma once


class IMaterial;
class Transform;

class Image
{
public:
	// ��Ԃ�ݒ肷��
	void SetIsActive(bool isActive) { m_isActive = isActive; }
	// ��Ԃ��擾����
	bool GetIsActive() { return m_isActive; }

	IMaterial* GetMaterial() { return m_material; }

	// ���C���̃e�N�X�`����ݒ肷��
	void SetTexture(ID3D11ShaderResourceView* texture, int& width, int& height);
	// ���[���e�N�X�`����ݒ肷��
	void SetRuleTexture(ID3D11ShaderResourceView* ruleTexture) { m_ruleTexture = ruleTexture; }

public:
	// �R���X�g���N�^
	Image();
	// �f�X�g���N�^
	~Image() = default;

	// ����������
	void Initialize(bool isActive, IMaterial* material, Transform* transform);
	// �`�揈��
	IMaterial* Render(ID3D11DeviceContext1* context, ID3D11Buffer* vertexBuffer);


private:
	// ��Ԑݒ�
	bool m_isActive;

	// �}�e���A��
	IMaterial* m_material;
	// �g�����X�t�H�[��
	Transform* m_transform;
	
	// ���C���e�N�X�`��
	ID3D11ShaderResourceView* m_texture;
	// ���[���e�N�X�`��
	ID3D11ShaderResourceView* m_ruleTexture;
};