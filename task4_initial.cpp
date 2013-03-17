namespace FMOD
{
    class Sound
    {
        //Класс для хранения звукового потока
        public:
            //загрузить звук из файла
            Sound(const std::string& filename);

            //скорость потока
            double bitrate() const;

            //полезные методы
            ...
    };

    class SoundCard
    {
        //Класс для работы со звуковой картой
        public:
            //полезные методы
            ...
            //воспроизвести звуковой поток через звуковую карту
            void Play(FMOD::Sound* sound);
    };
} //end of namespace FMOD

class MediaPlayer
{
    //Наш медиа-плеер
public:
    MediaPlayer()
    {
        soundCard = new FMOD::SoundCard(параметры инициализации);
        //Инициализируем остальные ресурсы
        ...
    }

    ~MediaPlayer()
    {
        for (std::list<FMOD::Sound*>::iterator it = playlist.begin(); it != playlist.end(); ++it)
            delete *it;
        delete soundCard;
        //Освобождаем остальные ресурсы
        ...
    }

    //Загрузка нового звуковой файл в плейер
    void Open(const std::string& filename)
    {
        playlist.push_back(new FMOD::Sound(filename));
    }

    //Воспроизведение звука
    void Play(const FMOD::Sound* sound)
    {
        soundCard->Play(sound);
    }

    //Другие полезные методы
    ...

private:
    FMOD::SoundCard* soundCard;
    std::list<FMOD::Sound*> playlist;
};
