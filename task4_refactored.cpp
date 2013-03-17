namespace MediaPlayer
{
  class Item
  {
  public:
    Item(const std::string& _filename): filename(_filename) {}

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
