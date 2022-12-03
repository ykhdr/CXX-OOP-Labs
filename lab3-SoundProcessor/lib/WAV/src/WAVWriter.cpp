#include "WAVWriter.hpp"

WAVWriter::WAVWriter(std::string path)
{
    outputFile_ = std::ofstream(path);

    if (!outputFile_.is_open())
    {
        throw std::invalid_argument("output file was not opened");
    }

    writeHeader();
}

void WAVWriter::writeHeader()
{
    WAVHeader::Chunk chunk =
            {
                    WAVSupportedFormat::RIFF,
                    0
            };

    outputFile_.write((char *) &chunk, sizeof(chunk));

    WAVHeader::format format = WAVSupportedFormat::WAVE;

    outputFile_.write((char *) &format, sizeof(format));

    WAVHeader::FMTChunkData fmtChunkData =
            {
                    WAVSupportedFormat::FMT_,
                    sizeof(fmtChunkData) - 3 * sizeof(uint32_t), // without subchunk1Id, subchunk2
                    WAVSupportedFormat::AUDIO_FORMAT_PCM,
                    WAVSupportedFormat::NUM_CHANNELS,
                    WAVSupportedFormat::SAMPLE_RATE,
                    WAVSupportedFormat::BYTE_RATE,
                    WAVSupportedFormat::BLOCK_ALIGN,
                    WAVSupportedFormat::BITS_PER_SAMPLE,
                    WAVSupportedFormat::DATA,
                    0
            };

    outputFile_.write((char *) &fmtChunkData, sizeof(fmtChunkData));
}

void WAVWriter::fixHeader()
{
    outputFile_.seekp(0, std::ios_base::end);
    uint32_t fSize = outputFile_.tellp();


    // Header chunk size
    outputFile_.seekp(
            sizeof(WAVSupportedFormat::RIFF),
            std::ios_base::beg);

    fSize -= sizeof(WAVHeader::Chunk);
    //TODO: проблемы с форматом файла
    outputFile_.write((char *) &fSize, sizeof(fSize));

    // Data size
    outputFile_.seekp(
            sizeof(WAVHeader::Chunk)
            + sizeof(WAVHeader::format)
            + sizeof(WAVHeader::FMTChunkData)
            - sizeof(WAVSupportedFormat::DATA),
            std::ios_base::beg);

    fSize -= sizeof(WAVHeader::format)
            + sizeof(WAVHeader::FMTChunkData);

    outputFile_.write((char *) &fSize, sizeof(fSize));

}

void WAVWriter::writeSample(SampleBuffer sampleBuffer)
{
    outputFile_.write((char *) &sampleBuffer[0], sizeof(sampleBuffer[0] * sampleBuffer.size()));

    if (!outputFile_.good())
    {
        throw std::exception();
    }
}
