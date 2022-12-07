#include "WAVWriter.hpp"
#include "WAVExceptions.hpp"

WAVWriter::WAVWriter(const std::string &path)
{
        outputFile_ = std::ofstream(path);

        if (!outputFile_.is_open())
        {
                throw std::invalid_argument("output file was not opened");
        }

        outputFilePath_ = std::move(path);

        writeHeader();
}

void WAVWriter::writeHeader()
{
        WAVHeader::Chunk riffChunk =
            {
                WAVSupportedFormat::RIFF,
                0};

        outputFile_.write((char *)&riffChunk, sizeof(riffChunk));

        WAVHeader::format format = WAVSupportedFormat::WAVE;

        outputFile_.write((char *)&format, sizeof(format));

        WAVHeader::Chunk fmtChunk =
            {
                WAVSupportedFormat::FMT_,
                sizeof(WAVHeader::FMTChunkData)};

        outputFile_.write((char *)&fmtChunk, sizeof(fmtChunk));

        WAVHeader::FMTChunkData fmtData =
            {
                WAVSupportedFormat::AUDIO_FORMAT_PCM,
                WAVSupportedFormat::NUM_CHANNELS,
                WAVSupportedFormat::SAMPLE_RATE,
                WAVSupportedFormat::BYTE_RATE,
                WAVSupportedFormat::BLOCK_ALIGN,
                WAVSupportedFormat::BITS_PER_SAMPLE};

        outputFile_.write((char *)&fmtData, sizeof(fmtData));

        WAVHeader::Chunk dataChunk =
            {
                WAVSupportedFormat::DATA,
                0};
        outputFile_.write((char *)&dataChunk, sizeof(dataChunk));
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
        outputFile_.write((char *)&fSize, sizeof(fSize));

        // Data size

        fSize -= sizeof(WAVHeader::format) + sizeof(WAVHeader::Chunk) + sizeof(WAVHeader::FMTChunkData) + sizeof(WAVHeader::Chunk);

        outputFile_.seekp(
            sizeof(WAVHeader::Chunk) + sizeof(WAVHeader::format) + sizeof(WAVHeader::Chunk) + sizeof(WAVHeader::FMTChunkData) + sizeof(WAVSupportedFormat::DATA),
            std::ios_base::beg);

        // fSize = 21894912;

        outputFile_.write((char *)&fSize, sizeof(fSize));
}

WAVWriter::~WAVWriter()
{
        fixHeader();
}

void WAVWriter::writeSample(SampleBuffer sampleBuffer)
{
        outputFile_.write((char *)&sampleBuffer, sizeof(Sample) * sampleBuffer.size());

        if (!outputFile_.good())
        {
                throw WAVExceptions::BadWritingFile(outputFilePath_);
        }
}
