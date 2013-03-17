// DONE: Base
// DONE: Base::SoundContainer
// DONE: Base::SoundAdapter
// DONE: copy FMOD::{Sound, SoundCard}
// DONE: FMOD::SoundContainer
// TODO: FMOD::SoundAdapter

// Somewhere in fmod.h, for example
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
}
// end of fmod.h

namespace Base
{
  class SoundContainer
  {
  public:
    SoundContainer() {}
    virtual ~SoundContainer() {}
  };

  class SoundAdapter
  {
  public:
    SoundAdapter() {}
    virtual ~SoundAdapter() {}

    virtual void Close(const Base::SoundContainer* container) = 0;
    virtual SoundContainer* Open(const std::string& filename) = 0;
    virtual void Play(const Base::SoundContainer* container) = 0;

    virtual double bitrate() const = 0;

    // Другие полезные функции
  };
}

namespace FMOD
{
  class SoundContainer
  {
  public:
    SoundContainer(const std::string& filename)
    {
      sound = new FMOD::Sound(filename);
    }

    ~SoundContainer()
    {
      delete sound;
    }

    FMOD::Sound* getSound() const { return sound; }

  private:
    FMOD::Sound* sound;
  };

  class SoundAdapter
  {
  public:
    SoundAdapter()
    {
      soundCard = new FMOD::Souncard(параметры инициализации);
    }

    ~SoundAdapter()
    {
      delete soundCard;
    }

    virtual void Close(const Base::SoundContainer* container)
    {
      // Метод вполне можно перенести в Base::SoundAdapter
      // а остальные действия поместить в деструктор
      // соответвующего ***::SoundContainer-а
      delete container;
    }

    virtual SoundContainer* Open(const std::string& filename)
    {
      // А вот это уже никуда не перенести
      FMOD::SoundContainer* container = new FMOD::SoundContainer(filename);
      return container;
    }

    // Воспроизведение звука
    virtual void Play(const Base::SoundContainer* container)
    {
      const FMOD::Sound* sound = container->getSound();
      soundCard->Play(sound);
    }

    virtual double bitrate() const
    {
      const FMOD::Sound* sound = container->getSound();
      return sound->bitrate();
    }

    // Другие полезные функции

  private:
    FMOD::SoundCard* soundCard;
  };
}

namespace MediaPlayer
{
  class Item
  {
  public:
    Item(const std::string& _filename):
      filename(_filename), adapter(0), container(0) {}

    ~Item()
    {
      if(adapter && container)
      {
        adapter->Close(container);
      }
    }

    void setSoundAdapter(const Base::SoundAdapter* _adapter)
    {
      if(adapter)
      {
        adapter->Close(container);
        container = 0;
      }

      adapter = _adapter;

      if(adapter)
      {
        container = adapter->Open(filename);
      }
    }

    void Play()
    {
      adapter->Play(container);
    }

    // Возможно, что здесь методов больше и не понадобится
    // Разве что на паузу поставить и т.п.

  private:
    std::string filename;
    Base::SoundAdapter* adapter;
    Base::SoundContainer* container;
  };

  class Application
  {
  public:
    Application(): adapter(0)
    {
      // Чистим playlist
      for(std::list<MediaPlayer::Item*>::iterator it = playlist.begin();
        it != playlist.end(); ++it) {
        delete *it;
      }

      // Чистим список проигрывателей
      for(std::list<Base::SoundAdapter*>::iterator it = adapters.begin();
        it != adapters.end(); ++it) {
        delete *it;
      }
    }

    // Добавление элемента списка проигрывания в плеер
    void Open(const std::string& filename)
    {
      MediaPlayer::Item* item = new MediaPlayer::Item(filename);
      if(adapter)
      {
        item->setSoundAdapter(adapter);
      }
      playlist.push_back();
    }

    //
    void Play(const MediaPlayer::Item* item)
    {
      item->Play();
    }

    // Другие полезные методы
    ...

  private:
    Base::SoundAdapter* adapter;
    std::list<Base::SoundAdapter*> adapters;
    std::list<MediaPlayer::Item*> playlist;
  };
}
