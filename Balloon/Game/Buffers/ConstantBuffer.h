#pragma once
#include <wrl/client.h>
#include <cstring> // for std::memcmp
#include <type_traits>
#include "Game/Buffers.h"


template<typename T>
class ConstantBuffer {
    static_assert(std::is_trivially_copyable_v<T>, "ConstantBuffer<T>: T must be trivially copyable");

public:
    ConstantBuffer() = default;

    // 初期化
    bool Initialize(ID3D11Device* device) {
        // 定数バッファ用のバッファオブジェクトを作成する
        D3D11_BUFFER_DESC bufferDesc{};
        bufferDesc.ByteWidth = static_cast<UINT>(sizeof(PBRLitConstantBuffer));	// 16の倍数を指定する
        bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
        bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
        bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
      
        return SUCCEEDED(device->CreateBuffer(&bufferDesc, nullptr, buffer.ReleaseAndGetAddressOf()));
    }

    // 値が変更された場合のみ更新
    void UpdateIfNeeded(ID3D11DeviceContext* context, const T& data) {
        if (std::memcmp(&cachedData, &data, sizeof(T)) != 0) 
        {
            D3D11_MAPPED_SUBRESOURCE mapped{};
            HRESULT hr = context->Map(buffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped);
            if (SUCCEEDED(hr)) 
            {
                std::memcpy(mapped.pData, &data, sizeof(T));

                context->Unmap(buffer.Get(), 0);
                cachedData = data;
            }
        }
    }

    // 強制更新（無条件に送信）
    void Update(ID3D11DeviceContext* context, const T& data) {
        context->UpdateSubresource(buffer.Get(), 0, nullptr, &data, 0, 0);
        cachedData = data;
    }

    ID3D11Buffer* GetBuffer() const noexcept {
        return buffer.Get();
    }

private:
    Microsoft::WRL::ComPtr<ID3D11Buffer> buffer;
    T cachedData{};  // 前回送信した内容
};