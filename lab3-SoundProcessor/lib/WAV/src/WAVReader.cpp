#include "WAVReader.hpp"

WAVReader::WAVReader(std::string filePath)
{
    open(std::move(filePath));
}

void WAVReader::open(std::string filePath)
{
   if (filePath.find(".wav") == std::string::npos)
    {
        // WAV exception about not format file
        throw std::exception();
    }

    inputFile_.open(filePath, std::ios_base::binary);
    if (!inputFile_.good())
    {
        // WAV exception about bad file opening
        throw std::exception();
    }

    readHeader();
}

void WAVReader::readHeader()
{
    WAVHeader::Chunk chunk;

    inputFile_.read((char *)&chunk, sizeof(chunk));

    if (!inputFile_.good() || chunk.chunkID != WAVSupportedFormat::RIFF)
    {
        // WAV exception about bad chunk format
        throw std::exception();
    }

    WAVHeader::format format;

    inputFile_.read((char *)&format, sizeof(format));

    if (!inputFile_.good() || format != WAVSupportedFormat::WAVE)
    {
        // WAV exception aboud bad format sym
        throw std::exception();
    }

    WAVHeader::FMTChunkData fmtData;

    inputFile_.read((char*)&fmtData,sizeof(fmtData));

    if(!inputFile_.good())
    {
        throw std::exception();
    }

    //TODO: подцепочки могут иметь другое нащвание, проверять иначе
    if(fmtData.subchunk2Id == WAVSupportedFormat::LIST)
    {
        inputFile_.ignore(fmtData.subchunk2Size);

        inputFile_.read((char*)&fmtData.subchunk2Id,sizeof(fmtData.subchunk2Id));
        inputFile_.read((char*)&fmtData.subchunk2Size,sizeof(fmtData.subchunk2Size));

    }

    if (!inputFile_.good()                                          ||

        fmtData.subchunk1Id != WAVSupportedFormat::FMT_             ||

        fmtData.audioFormat != WAVSupportedFormat::AUDIO_FORMAT_PCM ||

        fmtData.numChannels != WAVSupportedFormat::NUM_CHANNELS     ||

        fmtData.sampleRate != WAVSupportedFormat::SAMPLE_RATE       ||

        fmtData.subchunk2Id != WAVSupportedFormat::DATA)
    {
        // WAV excetpion about bad FMT data format
        throw std::exception();
    }
}

bool WAVReader::readSample(SampleBuffer &sampleBuffer)
{
    inputFile_.read((char*) &sampleBuffer[0], sizeof(sampleBuffer[0]) * sampleBuffer.size());

    if(inputFile_.gcount()==0)
    {
        sampleBuffer.fill(0);
    }

    return inputFile_.gcount();
}