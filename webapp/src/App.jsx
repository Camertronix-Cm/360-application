
import { Home } from './pages/home.jsx'
import './index.css'
import { BrowserRouter as Router, Route, Routes } from 'react-router-dom'
import { Layout } from './components/Layout.jsx'
import VideoPage from './pages/video.jsx'


function App() {
  return (

    
    <Router>
    <Layout> 
      <Routes>
        <Route path="/" element={<Home />} />
        <Route path="/video" element={<VideoPage />} />
        <Route path="/video/:title" element={<VideoPage />} />
      </Routes>
      </Layout>
    </Router>
    

  )
}

export default App