#pragma once
#include <vector>
#include <span>

class BasicReaderWriter
{
public:
    BasicReaderWriter();
    BasicReaderWriter(
        _In_ winrt::Windows::Storage::StorageFolder folder
    );
public:
    std::vector<std::byte> ReadData(
        _In_ winrt::hstring const& filename
    );

    winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Storage::Streams::IBuffer> ReadDataAsync(
        _In_ winrt::hstring const& filename
    );

    uint32_t WriteData(
        _In_ winrt::hstring const& filename,
        _In_ std::span<const uint8_t> fileData
    );

    winrt::Windows::Foundation::IAsyncAction WriteDataAsync(
        _In_ winrt::hstring const& filename,
        _In_ std::span<const uint8_t> fileData
    );

private:
    winrt::Windows::Storage::StorageFolder m_location{ nullptr };
};